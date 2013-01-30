/////////////////////////////////////////////////////////////////////////
// PixelArth
// Copyright (C) 2012  Viktor Was <viktor.was@technikum-wien.at>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
/////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include <iostream>
#include <fstream>

#include "Bitmask.h"
#include "Physics/stb_image.c"

Bitmask::Bitmask(const String& path)
	: m_path(path)
{
	loadMask(m_path);
    m_original_mask = nullptr;
};

Bitmask::Bitmask(const String& path, const Bitmask * const original)
	: m_path(path)
{
	loadMask(m_path);
    m_original_mask = original;
};

/// <summary>Destructor</summary>
Bitmask::~Bitmask(void)
{
	stbi_image_free(m_mask);
};

/// <summary>Loads bitmask from file
/// <para>Sets m_size and m_type</para></summary>
/// <param name="path">Path to the bitmask file</param>
void Bitmask::loadMask(const String& path)
{
    m_mask = stbi_load(path.c_str(),&m_size.X,&m_size.Y,&m_type,1);
	if (m_mask == NULL) std::cout<<"cant inizialise mask! inputfile: "<<path<<std::endl;
	else
	std::cout << "Bitmask created! x: " << m_size.X << " y: " << m_size.Y << " type: " << m_type << " inputfile: " << path << std::endl;
};

/// <summary>Get the path to the bitmask file</summary>
/// <return>Bitmask file path</return>
String Bitmask::getPath(void) const
{
	return m_path;
};

/// <summary>Resizes the bitmask
/// <para>If an originally sized bitmask is given, it is being used for resizing</para></summary>
/// <param name="sizeX">Horizontal size (in pixels)</param>
/// <param name="sizeY">Vertical size (in pixels)</param>
void Bitmask::setSize(const float sizeX, const float sizeY){
    const Bitmask* maskToScale = m_original_mask != nullptr ? m_original_mask : this;
    
    // check if this bitmask isn't the same as the one in the hashmap
    int i,j;
	float scaleX,scaleY;
	m_size.X= ceil(MathUtil::WorldUnitsToPixels(sizeX));
	m_size.Y= ceil(MathUtil::WorldUnitsToPixels(sizeY));
	scaleX=(float)maskToScale->getPixelSize().X/(float)m_size.X;
	scaleY=(float)maskToScale->getPixelSize().Y/(float)m_size.Y;
	m_mask = new unsigned char[m_size.X*m_size.Y];
	for(i=0;i<m_size.X;i++)
	{
		for(j=0;j<m_size.Y;j++)
		{
			m_mask[j*m_size.X+i] = maskToScale->getBit((int)((float)i*scaleX),(int)((float)j*scaleY));
		}
	}
};

/// <summary>Resizes the bitmask</summary>
/// <param name="size">Size (in pixels)</param>
void Bitmask::setSize(const Vector2& size){
    Bitmask::setSize(size.X, size.Y);
};

/// <summary>Gets the bit on the given pixel position</summary>
/// <param name="xPos">Horizontal Position of the bit</param>
/// <param name="yPos">Vertical Position of the bit</param>
/// <return>The bit at the requested position</return>
unsigned char Bitmask::getBit(const int xPos, const int yPos) const
{
    if (m_mask!=NULL)
        return m_mask[yPos*m_size.X + xPos];
	return '\n';
};

/// <summary>Gets the bit on the given pixel position</summary>
/// <param name="xPos">Position of the bit</param>
/// <return>The bit at the requested position</return>
unsigned char Bitmask::getBit(const Vec2i& pos) const
{
    return Bitmask::getBit(pos.X, pos.Y);
};

/// <summary>Roughly prints the bitmask into a file</summary>
void Bitmask::printMask() const
{
     int i, j;
    std::ofstream myfile;
    myfile.open ("mask.txt", std::ios::app);
    myfile<<m_path<<"\n";

    for(i= 0;i<getPixelSize().Y;i++)
    {
        //myfile << i << ". ";
        for(j=0;j<getPixelSize().X;j++)
        {
            myfile<<(short int)getBit(j,i)<<"|";
        }
        myfile<<"\n";
    }
}