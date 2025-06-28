#include <windows.h>
#include <mmdeviceapi.h>
#include <audiopolicy.h>
#include <functiondiscoverykeys_devpkey.h>
#include <psapi.h>
#include <iostream>
#include <vector>
#include <map>
#include <comdef.h>
#include <Unknwn.h> // Para IUnknown base

#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "Uuid.lib")
#pragma comment(lib, "Psapi.lib")

// Definição manual da interface IAudioMeterInformation

// IID da interface IAudioMeterInformation
// {C02216F6-8C67-4B5B-9D00-D008E73E0064}
static const GUID IID_IAudioMeterInformation = 
{ 0xc02216f6, 0x8c67, 0x4b5b, { 0x9d, 0x00, 0xd0, 0x08, 0xe7, 0x3e, 0x00, 0x64 } };

struct IAudioMeterInformation : public IUnknown {
    virtual HRESULT STDMETHODCALLTYPE GetPeakValue(float *pfPeak) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetMeteringChannelCount(UINT *pnChannelCount) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetChannelsPeakValues(UINT32 u32ChannelCount, float *afPeakValues) = 0;
};

// Estrutura para manter dados da sessão de áudio
struct AudioSessionInfo {
    DWORD pid;
    std::wstring processName;
    ISimpleAudioVolume* pVolume;
    IAudioMeterInformation* pMeterInfo;
    UINT channelCount = 0;
    std::vector<float> channelPeaks;
};

std::wstring GetProcessName(DWORD pid) {
    std::wstring name = L"<unknown>";
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (hProcess) {
        wchar_t buffer[MAX_PATH] = {};
        if (GetModuleBaseNameW(hProcess, nullptr, buffer, MAX_PATH)) {
            name = buffer;
        }
        CloseHandle(hProcess);
    }
    return name;
}

void ClearScreen() {
    system("cls");
}

void ShowBarGraph(float level) {
    int bars = static_cast<int>(level * 20);
    std::wcout << L"[" << std::wstring(bars, L'#') << std::wstring(20 - bars, L'.') << L"] ";
    std::wcout << (int)(level * 100) << L"%";
}

std::vector<AudioSessionInfo> GetAudioSessions() {
    std::vector<AudioSessionInfo> sessions;

    IMMDeviceEnumerator* pEnumerator = nullptr;
    IMMDevice* pDevice = nullptr;
    IAudioSessionManager2* pSessionManager = nullptr;
    IAudioSessionEnumerator* pSessionList = nullptr;

    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL,
                     __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
    if (FAILED(hr) || !pEnumerator) return sessions;

    hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
    if (FAILED(hr) || !pDevice) {
        pEnumerator->Release();
        return sessions;
    }

    hr = pDevice->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL, nullptr, (void**)&pSessionManager);
    if (FAILED(hr) || !pSessionManager) {
        pDevice->Release();
        pEnumerator->Release();
        return sessions;
    }

    hr = pSessionManager->GetSessionEnumerator(&pSessionList);
    if (FAILED(hr) || !pSessionList) {
        pSessionManager->Release();
        pDevice->Release();
        pEnumerator->Release();
        return sessions;
    }

    int sessionCount = 0;
    pSessionList->GetCount(&sessionCount);

    for (int i = 0; i < sessionCount; i++) {
        IAudioSessionControl* pSessionControl = nullptr;
        IAudioSessionControl2* pSessionControl2 = nullptr;

        hr = pSessionList->GetSession(i, &pSessionControl);
        if (FAILED(hr) || !pSessionControl) continue;

        hr = pSessionControl->QueryInterface(__uuidof(IAudioSessionControl2), (void**)&pSessionControl2);
        pSessionControl->Release();
        if (FAILED(hr) || !pSessionControl2) continue;

        DWORD pid = 0;
        pSessionControl2->GetProcessId(&pid);

        ISimpleAudioVolume* pVolume = nullptr;
        hr = pSessionControl2->QueryInterface(__uuidof(ISimpleAudioVolume), (void**)&pVolume);

        IAudioMeterInformation* pMeterInfo = nullptr;
        hr = pSessionControl2->QueryInterface(IID_IAudioMeterInformation, (void**)&pMeterInfo);

        std::wstring procName = GetProcessName(pid);

        AudioSessionInfo asi;
        asi.pid = pid;
        asi.processName = procName;
        asi.pVolume = pVolume;
        asi.pMeterInfo = pMeterInfo;
        asi.channelCount = 0;

        if (pMeterInfo) {
            UINT channelCount = 0;
            if (SUCCEEDED(pMeterInfo->GetMeteringChannelCount(&channelCount)) && channelCount > 0) {
                asi.channelCount = channelCount;
                asi.channelPeaks.resize(channelCount);
            }
        }

        sessions.push_back(asi);

        pSessionControl2->Release();
    }

    pSessionList->Release();
    pSessionManager->Release();
    pDevice->Release();
    pEnumerator->Release();

    return sessions;
}

int main() {
    CoInitialize(nullptr);

    std::vector<AudioSessionInfo> sessions;

    int frame = 0;
    while (true) {
        if (frame++ % 5 == 0) {
            for (auto& s : sessions) {
                if (s.pVolume) s.pVolume->Release();
                if (s.pMeterInfo) s.pMeterInfo->Release();
            }
            sessions = GetAudioSessions();
        }

        ClearScreen();
        std::wcout << L"Monitorando " << sessions.size() << L" sessoes de audio:\nPressione DEL para sair\n\n";

        for (auto& session : sessions) {
            float level = 0.0f;
            if (session.pVolume && SUCCEEDED(session.pVolume->GetMasterVolume(&level))) {
                std::wcout << session.processName << L" (PID " << session.pid << L") | Volume: ";
                ShowBarGraph(level);

                if (session.pMeterInfo && session.channelCount > 0) {
                    session.pMeterInfo->GetChannelsPeakValues(session.channelCount, session.channelPeaks.data());
                    std::wcout << L" | \n   Picos por canal: ";
                    for (UINT c = 0; c < session.channelCount; c++) {
                        int bars = static_cast<int>(session.channelPeaks[c] * 10);
                        std::wcout << L"\n      [" << std::wstring(bars, L'#') << std::wstring(10 - bars, L'.') << L"] ";
                    }
                }

                std::wcout << std::endl;
            }
        }

        for (int i = 0; i < 30; i++) {
            if (GetAsyncKeyState(VK_DELETE) & 0x8000) {
                return 0;
            }
            Sleep(10);
        }
    }

    for (auto& s : sessions) {
        if (s.pVolume) s.pVolume->Release();
        if (s.pMeterInfo) s.pMeterInfo->Release();
    }

    CoUninitialize();
    return 0;
}
