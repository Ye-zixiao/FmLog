//
// Created by Ye-zixiao on 2021/7/27.
//

#include <string>
#include <string_view>
#include <iostream>
#include "util/LogLine.h"
using namespace std;
using namespace fm::log;

int main() {
  char buf[32] = "test my log code";
  const char *const psubstr = &buf[5];

  LogLine log_line_error(LogLevel::kERROR, 1, __FILE__, __LINE__);
  log_line_error << 32 << ' ';
  log_line_error << 43u << ' ';
  log_line_error << -47284 << ' ';
  log_line_error << INT64_MAX << ' ';
  log_line_error << INT32_MIN << ' ';
  log_line_error << INT32_MAX << ' ';
  log_line_error << INT64_MIN << ' ';
  log_line_error << 473.32 << ' ';
  log_line_error << -324.32 << ' ';

  LogLine log_line_info(LogLevel::kDEBUG, 0, __FILE__, __LINE__);
  log_line_info << "hello world" << ' ';
  log_line_info << std::string(" show me the code") << ' ';
  log_line_info << std::string_view(" talk is cheap") << ' ';
  log_line_info << buf << ' ';
  log_line_info << psubstr << ' ';
  log_line_info << std::string("fasdjklk;l;l;l;l;l;l;l;kkkkkkl;kl;kkl;kl;kl;lk;lk;"
                               "lk;lk;kl;kl;kl;kl;lk;kl;kl;l;l;l;l;fjkflsda;sdsdsdsdsd"
                               "sdsdsdsdsdsd;sd;sd;sd;sd;sd;sd;sd;sd;sd;sd;sd;sd;sd;sd"
                               ";sd;sd;sdfjsdkjklsdfjklsdjfsdhfsdajkhajkajkhajkhajkhaj"
                               "khahjkajkhajkhajkhajkhajkhajkhajkhajkhfdjsfjsfhjdsk;;;;"
                               ";;;;;jfdklsssssssssssssssssssssssssssssssssssssssssssss"
                               "ssssssssssssssssdfjjfdlong string");

  log_line_error.stringify(cout);
  log_line_info.stringify(cout);

  return 0;
}