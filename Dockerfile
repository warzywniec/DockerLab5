# Etap 1: budowanie aplikacji i curl w Alpine zamiast ngingx, ponieważ finalny obraz jest w scratchu
FROM alpine:latest AS builder

RUN apk add --no-cache gcc musl-dev curl

# Kompilacja
WORKDIR /app
COPY main.c .
ARG VERSION=DEV
RUN gcc -static -DVERSION="\"${VERSION}\"" -o myapp main.c

# Etap 2: Finalny obraz Scratch
FROM scratch

# Dodanie binarki skompilowanej aplikacji do obrazu
COPY --from=builder /app/myapp /myapp

# Dodanie curl do obrazu w celu użycia HEALTHCHECK
# Potrzebne w celu wykonania zadania jako, że w Scratchu nie ma /bin/sh
COPY --from=builder /usr/bin/curl /curl

# HEALTHCHECK
HEALTHCHECK --interval=10s --timeout=1s CMD ["/curl", "-f", "http://localhost:8080"] || exit 1

# PORT
EXPOSE 8080

ENTRYPOINT ["/myapp"]
