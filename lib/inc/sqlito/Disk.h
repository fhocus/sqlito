/**
 * @file Disk.h
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

#include <iostream>
#include <string>

namespace SQLito
{
  class Disk
  {
  private:
    size_t _capacity;
    size_t _used;

    unsigned int _platters;
    unsigned int _tracks;
    unsigned int _sectors;
    unsigned int _sectorSize;

  public:
    Disk();
    ~Disk();

    size_t getCapacity() const;
    size_t getUsed() const;

    unsigned int getPlatters() const;
    unsigned int getTracks() const;
    unsigned int getSectors() const;
    unsigned int getSectorSize() const;

    void setCapacity(size_t);
    void setUsed(size_t);

    void setPlatters(unsigned int);
    void setTracks(unsigned int);
    void setSectors(unsigned int);
    void setSectorSize(unsigned int);

    friend std::ostream &operator<<(std::ostream &, const Disk &);
  };
}