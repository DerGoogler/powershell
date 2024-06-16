#include "pstream.h"
#include <string>
#include <iostream>

int main()
{
  // run a process and create a streambuf that reads its stdout and stderr
  redi::ipstream proc("setenforce 0 && su -c am start -a android.intent.action.VIEW -d 'https://youtu.be/dQw4w9WgXcQ' && setenforce 1", redi::pstreams::pstdout | redi::pstreams::pstderr);
  std::string line;
  // read child's stdout
  while (std::getline(proc.out(), line))
    std::cout << "stdout: " << line << '\n';
  // if reading stdout stopped at EOF then reset the state:
  if (proc.eof() && proc.fail())
    proc.clear();
  // read child's stderr
  while (std::getline(proc.err(), line))
    std::cout << "stderr: " << line << '\n';
}