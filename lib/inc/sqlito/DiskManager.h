/**
 * @file DiskManager.h
 * @author Fabricio Huaquisto <fhuaquisto@unsa.edu.pe>
 * @author Johan Lizarve <jlizarve@unsa.edu.pe>
 *
 * Copyright (c) 2024 Universidad Nacional de San Agustin (UNSA)
 * https://github.com/fhocus/sqlito
 *
 * SQLito
 *
 */

#pragma once

#include <sqlito/Disk.h>
#include <string>

namespace SQLito
{
  class DiskManager
  {
  private:
    std::string _diskName;
    std::string _diskPath;
    Disk *_disk;

    std::string getDiskInfo(std::string);
    std::string getDiskInfo(std::string, Disk *);

  public:
    DiskManager();
    ~DiskManager();

    int loadDisk(std::string, std::string);
    int saveDisk(std::string, std::string);
    int saveDisk(std::string, std::string, unsigned int, unsigned int, unsigned int, unsigned int);
  };
}