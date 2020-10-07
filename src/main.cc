#include <iostream>
#include <thread>

#include <opencv2/core/mat.hpp>

#include "http_server.h"
#include "photo_album.h"
#include "rtsp_server.h"

int main(int argc, char** argv) {
  using namespace vrc_photo_streamer;

  http::http_server http_server;
  std::thread hs([&http_server] { http_server.run(); });

  photo::photo_album album;
  album.find_images();
  album.update({0, 4});
  cv::Mat frame = album.get_frame();

  rtsp::rtsp_server rtsp_server;
  rtsp_server.initialize(argc, argv, frame, frame.total() * frame.channels());

  std::thread rs([&rtsp_server] { rtsp_server.run(); });

  hs.join();
  rs.join();
  return 0;
}
