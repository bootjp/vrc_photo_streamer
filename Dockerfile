FROM archlinux:latest

RUN pacman --noconfirm -Sy gcc git glib2 util-linux-libs meson cmake ninja unzip opencv gstreamer gst-plugins-base gst-plugins-good gst-plugins-ugly gst-plugins-bad

RUN curl -SsLO https://github.com/GStreamer/gst-rtsp-server/archive/1.18.0.zip
RUN unzip 1.18.0.zip
RUN cd gst-rtsp-server-1.18.0 && meson build
COPY ./ /app/
RUN mkdir build && cd $_
RUN cmake .. -G ninja
RUN ninja
RUN ./bin/vrc_photo_streamer

