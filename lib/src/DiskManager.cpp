/**
 * @file DiskManager.cpp
 * @author Fabricio Huaquisto <fhuaquisto@unsa.edu.pe>
 *
 * Copyright (c) 2024 Universidad Nacional de San Agustin (UNSA)
 * https://github.com/fhocus/sqlito
 *
 * SQLito
 *
 */

#include <sqlito/DiskManager.h>
#include <sqlito/utils/File.h>
#include <iostream>

namespace SQLito
{
  DiskManager::DiskManager()
  {
    _disk = new Disk();
  }

  DiskManager::~DiskManager()
  {
    delete _disk;
  }

  int DiskManager::loadDisk(std::string databaseFolder, std::string diskName)
  {
    std::string diskPath = databaseFolder + "/" + diskName;

    if (Utils::createDirectory(diskPath))
      return -1;

    std::fstream file = Utils::getFile(diskPath + "/info", std::ios::in);
    std::string token;

    file >> token;
    if (token != diskName)
      return -1;

    while (file >> token)
    {
      std::string type = token;
      file >> token;
      if (type == "Capacity:")
        _disk->setCapacity(std::stoi(token));
      else if (type == "Used:")
        _disk->setUsed(std::stoi(token));
      else if (type == "Platters:")
        _disk->setPlatters(std::stoi(token));
      else if (type == "Tracks:")
        _disk->setTracks(std::stoi(token));
      else if (type == "Sectors:")
        _disk->setSectors(std::stoi(token));
      else if (type == "SectorSize:")
        _disk->setSectorSize(std::stoi(token));
    }

    return 1;
  }

  int DiskManager::saveDisk(std::string databaseFolder, std::string diskName)
  {
    return saveDisk(databaseFolder, diskName, 2, 8, 16, 2048);
  }

  int DiskManager::saveDisk(std::string databaseFolder, std::string diskName, unsigned int platters, unsigned int tracks, unsigned int sectors, unsigned int sectorSize)
  {
    std::string diskPath = databaseFolder + "/" + diskName;
    if (platters == 0 || tracks == 0 || sectors == 0 || sectorSize == 0)
      return -1;

    if (!Utils::createDirectory(diskPath))
      return 0;

    Disk *disk = new Disk();
    disk->setPlatters(platters);
    disk->setTracks(tracks);
    disk->setSectors(sectors);
    disk->setSectorSize(sectorSize);
    disk->setCapacity(platters * tracks * sectors * sectorSize);

    for (unsigned int p = 0; p < platters; p++)
    {
      std::string pathPlatter = diskPath + "/" + std::to_string(p);
      for (unsigned int t = 0; t < tracks; t++)
      {
        std::string pathTrack = pathPlatter + "/" + std::to_string(t);
        Utils::createDirectory(pathTrack);
        for (unsigned int s = 0; s < sectors; s++)
        {
          std::string pathSector = pathTrack + "/" + std::to_string(s);
          Utils::getFile(pathSector, std::ios::out);
        }
      }
    }

    Utils::getFile(diskPath + "/info", std::ios::out) << getDiskInfo(diskName, disk);

    delete disk;

    return 1;
  }

  std::string DiskManager::getDiskInfo(std::string diskName)
  {
    std::string info = diskName + "\n";
    info += "Capacity: " + std::to_string(_disk->getCapacity()) + "\n";
    info += "Used: " + std::to_string(_disk->getUsed()) + "\n";
    info += "Platters: " + std::to_string(_disk->getPlatters()) + "\n";
    info += "Tracks: " + std::to_string(_disk->getTracks()) + "\n";
    info += "Sectors: " + std::to_string(_disk->getSectors()) + "\n";
    info += "SectorSize: " + std::to_string(_disk->getSectorSize()) + "\n";
    return info;
  }

  std::string DiskManager::getDiskInfo(std::string diskName, Disk *disk)
  {
    std::string info = diskName + "\n";
    info += "Capacity: " + std::to_string(disk->getCapacity()) + "\n";
    info += "Used: " + std::to_string(disk->getUsed()) + "\n";
    info += "Platters: " + std::to_string(disk->getPlatters()) + "\n";
    info += "Tracks: " + std::to_string(disk->getTracks()) + "\n";
    info += "Sectors: " + std::to_string(disk->getSectors()) + "\n";
    info += "SectorSize: " + std::to_string(disk->getSectorSize()) + "\n";
    return info;
  }
}