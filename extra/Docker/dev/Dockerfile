FROM ubuntu:24.04 AS build

RUN apt-get update && apt-get install -y \
 git \
 vim \
 make \
 g++ \
 libsdl1.2-dev \
 virtualenv \
 && groupadd -r VigasocoSDL \
 && useradd --no-log-init -r -m -s /bin/bash -g VigasocoSDL abadIA

USER abadIA

WORKDIR /home/abadIA

ENV LC_ALL=C.UTF-8
ENV DISPLAY=:0

RUN cd /home/abadIA \
  && bash -c "virtualenv -p python3 python3 && \
  source python3/bin/activate \
  && pip install behave fastmcp==2.5.1 \
  && git clone https://github.com/LaAbadIAdelCrimen/VigasocoSDL-AI.git \
  && cd VigasocoSDL-AI \
  && git checkout libabadia \
  && git submodule update --init --recursive \
  && make clean \
  && make -f Makefile.libabadia"

EXPOSE 4477

WORKDIR /home/abadIA/VigasocoSDL-AI/extra/mcp-server/mcp
ENTRYPOINT ["bash", "-c", "source /home/abadIA/python3/bin/activate && python abadIA-MCP.py"]
