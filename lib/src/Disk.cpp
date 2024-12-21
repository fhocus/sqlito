/**
 * @file Disk.cpp
 * @author Fabricio Huaquisto <fhuaquisto@unsa.edu.pe>
 *
 * Copyright (c) 2024 Universidad Nacional de San Agustin (UNSA)
 * https://github.com/fhocus/sqlito
 *
 * SQLito
 *
 */

#include <sqlito/Disk.h>

namespace SQLito
{
  Disk::Disk()
  {
    _capacity = 0;
    _used = 0;

    _platters = 0;
    _tracks = 0;
    _sectors = 0;
    _sectorSize = 0;
  }

  Disk::~Disk() {}

  size_t Disk::getCapacity() const
  {
    return _capacity;
  }

  size_t Disk::getUsed() const
  {
    return _used;
  }

  unsigned int Disk::getPlatters() const
  {
    return _platters;
  }

  unsigned int Disk::getTracks() const
  {
    return _tracks;
  }

  unsigned int Disk::getSectors() const
  {
    return _sectors;
  }

  unsigned int Disk::getSectorSize() const
  {
    return _sectorSize;
  }

  void Disk::setCapacity(size_t capacity)
  {
    _capacity = capacity;
  }

  void Disk::setUsed(size_t used)
  {
    _used = used;
  }

  void Disk::setPlatters(unsigned int platters)
  {
    _platters = platters;
  }

  void Disk::setTracks(unsigned int tracks)
  {
    _tracks = tracks;
  }

  void Disk::setSectors(unsigned int sectors)
  {
    _sectors = sectors;
  }

  void Disk::setSectorSize(unsigned int sectorSize)
  {
    _sectorSize = sectorSize;
  }

  std::ostream &operator<<(std::ostream &os, const Disk &disk)
  {
    os << "Disk (" << "\n";
    os << "\tCapacity: " << disk.getCapacity() << "\n";
    os << "\tUsed: " << disk.getUsed() << "\n";
    os << "\tPlatters: " << disk.getPlatters() << "\n";
    os << "\tTracks: " << disk.getTracks() << "\n";
    os << "\tSectors: " << disk.getSectors() << "\n";
    os << "\tSector Size: " << disk.getSectorSize() << "\n";
    os << ")";
    return os;
  }
}