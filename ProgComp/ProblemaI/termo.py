def termo(n, vec=[1, 1, 1, 2, 2, 3, 4, 5, 7, 9, 12, 16]):
    while len(vec) < n:
        i = len(vec)
        prox = vec[i-1] + vec[i-5]
        vec.append(prox)
    return vec[n - 1]

def main():
    while True:
        try:
            n = int(input())
            print(termo(n))
        except EOFError:
            break

if __name__ == "__main__":
    main()
