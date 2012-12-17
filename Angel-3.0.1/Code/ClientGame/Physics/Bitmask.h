#pragma once

/// <summary></summary>
class Bitmask
{
public:
	/// <summary>Constructor</summary>
	/// <param name="path">Describes the path to the bitmask file
	/// <para>e.g. "Resources/Images/..."</para></param>
	Bitmask(const String& path);

    /// <summary>Destructor</summary>
	~Bitmask(void);

	/// <returns>Returns the path to the bitmask</returns>
	String getPath(void) const;

    /// <summary>Copies and resizes the bitmask</summary>
    /// <param name="x">Size along x-axis (in GL units).</param>
    /// <param name="y">Size along y-axis (in GL units). By default -1.0f for a uniform scale.</param>
	void setSize(const float& sizeX, const float& sizeY = -1.0f);
	
    /// <summary>Copies and resizes the bitmask</summary>
    /// <param name="size">The size of the bitmask (in GL units).</param>
    void setSize(const Vector2& size);

	/// <returns>Returns the size of the bitmask (in GL units)</returns>
    inline Vector2 getSize(void) const
    { return Vector2(MathUtil::PixelsToWorldUnits(m_size.X), MathUtil::PixelsToWorldUnits(m_size.Y)); };

	/// <returns>Returns the size of the bitmask (in pixels)</returns>
    inline Vec2i getPixelSize(void) const { return m_size; };

    /// <returns>Returns the type of the bitmask file
    /// <para>TODO: Describe return values!!!</para></returns>
    inline int getType(void) const { return m_type; };

    /// <returns>TODO</returns>
    inline unsigned char * getMask() const { return m_mask; };

    /// <summary>TODO</summary>
    /// <param name="xPos">X coord describing the position of a bit (in pixels)</param>
    /// <param name="yPos">Y coord describing the position of a bit (in pixels)</param>
    /// <returns>TODO</returns>
    unsigned char getBit(const int& xPos, const int& yPos) const;

    /// <summary>TODO</summary>
    /// <param name="pos">Position describing a bit (in pixels)</param>
    /// <returns>TODO</returns>
    unsigned char getBit(const Vec2i& pos) const;
private:
    //Bitmask (const Bitmask &);
    //Bitmask &operator= (const Bitmask &);

    /// <summary></summary>
	void loadMask(const String& path);

    Vec2i m_size;
    int m_type;
    unsigned char * m_mask;
    String m_path;
};