FROM mcr.microsoft.com/windows/nanoserver:ltsc2022

ENV chocolateyUseWindowsCompression false

SHELL ["powershell", "-Command"]
RUN [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; \
    iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1')); \
    choco feature enable -n allowGlobalConfirmation

RUN choco install visualstudio2019buildtools --version=16.11.5.0 --package-parameters "--passive --includeRecommended --add Microsoft.VisualStudio.Workload.VCTools --includeOptional"

RUN choco install cmake --installargs 'ADD_CMAKE_TO_PATH=System'

WORKDIR /app

COPY . .

RUN mkdir build
WORKDIR /app/build
RUN "C:\\BuildTools\\Common7\\Tools\\VsDevCmd.bat" -arch=amd64 -host_arch=amd64 && cmake .. && cmake --build .

CMD ["build\\AUTOSKP2GLB.exe"]
