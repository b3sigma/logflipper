#include <memory>
#include <stdio.h>
#include <list>
#include <vector>
#include <set>
#include <unordered_map>
#include <hash_map>
#include <algorithm>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{

  if(argc < 3) {
    printf("Usage whateveryoujusttyped.exe readFileName writeFileName\n");
    return -1;
  }

  const char* readFilename = argv[1];
  const char* writeFilename = argv[2];

  std::ifstream readFile(readFilename);
  if(!readFile.is_open()) {
    printf("Couldn't open %s for reading\n", readFilename);
    return -1;
  }

  std::ofstream writeFile(writeFilename);
  if(!writeFile.is_open()) {
    printf("Couldn't open %s for writing\n", writeFilename);
    return -1;
  }

  typedef std::list<std::string> Entries;
  Entries entries;

  std::string currentEntry;
  std::string line;
  while(std::getline(readFile, line)) {
    if(strstr(line.c_str(), "===") != NULL) {
      if(!currentEntry.empty()) {
        entries.push_back(currentEntry);
      }
      currentEntry.clear();
    }

    currentEntry += line;
    currentEntry += "\n";
  }
  if(!currentEntry.empty()) {
    entries.push_back(currentEntry);
  }
  readFile.close();

  for(auto entryIt = entries.rbegin();
    entryIt != entries.rend();
    ++entryIt) {
    writeFile << (*entryIt);
  }
  writeFile.close();

  return 0;
}

