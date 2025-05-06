# DockerLab5
Zadanie z Laboratorium 5 w ramach przedmiotu, Programowanie Aplikacji w Chmurze Obliczeniowej

### Aplikacja serwerowa napisana w C "main.c" oraz plik tworzący obraz "Dockerfile"

### Polecenie w celu budowy obrazu

```docker build --build-arg VERSION=1.2.0 -t testlab5:1.0.0 .```
 Wynik polecenia:
```
[+] Building 1.4s (11/11) FINISHED                                                                 docker:desktop-linux
 => [internal] load build definition from Dockerfile                                                               0.0s
 => => transferring dockerfile: 374B                                                                               0.0s
 => [internal] load metadata for docker.io/library/alpine:latest                                                   0.6s
 => [internal] load .dockerignore                                                                                  0.0s
 => => transferring context: 2B                                                                                    0.0s
 => [internal] load build context                                                                                  0.1s
 => => transferring context: 2.04kB                                                                                0.0s
 => [builder 1/5] FROM docker.io/library/alpine:latest@sha256:a8560b36e8b8210634f77d9f7f9efd7ffa463e380b75e2e74af  0.0s
 => => resolve docker.io/library/alpine:latest@sha256:a8560b36e8b8210634f77d9f7f9efd7ffa463e380b75e2e74aff4511df3  0.0s
 => CACHED [builder 2/5] RUN apk add --no-cache build-base                                                         0.0s
 => CACHED [builder 3/5] WORKDIR /app                                                                              0.0s
 => [builder 4/5] COPY main.c .                                                                                    0.0s
 => [builder 5/5] RUN gcc -static -DVERSION=""1.2.0"" -o app main.c                                                0.3s
 => [stage-1 1/1] COPY --from=builder /app/app /app/app                                                            0.0s
 => exporting to image                                                                                             0.2s
 => => exporting layers                                                                                            0.1s
 => => exporting manifest sha256:c94a6e797a90203acb8aaf7688212e5281935d258de5b36787131bc03806b56b                  0.0s
 => => exporting config sha256:3b642f0874a32526afe4b55e774247fe1b34386742063e76b6f3b92c0d717f15                    0.0s
 => => exporting attestation manifest sha256:c2a712d6d827ada9f652f148688e72105624aa1b0086dec9af6db7e6106b728c      0.0s
 => => exporting manifest list sha256:fcba155b4cd97ace84a6fa91c242f3630fa58c3a3e2581717dc853491ab62733             0.0s
 => => naming to docker.io/library/testlab5:1.0.0                                                                  0.0s
 => => unpacking to docker.io/library/testlab5:1.0.0                                                               0.0s
```

### Polecenie uruchamiające serwer

``` docker run -d -p 8080:8080 --name test --rm testlab5:1.0.0 ```

### Polecenie potwierdzające działanie kontenera i poprawne funkcjonowanie opracowanej aplikacji

``` curl http://localhost:8080 ```

### Zrzut ekranu

![Screenshot 2025-05-06 151736](https://github.com/user-attachments/assets/1e781f31-8425-4266-992d-8cb489ee6f6b)
