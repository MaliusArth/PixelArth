%module angel
%{
#include "../../Infrastructure/Color.h"
%}

#ifdef SWIGLUA
%typemap(in) Color
{
	// convert table parameters to floats
	lua_pushinteger(L, 1);
	lua_gettable(L, $input);
	float r = lua_tonumber(L, -1);
	lua_pop(L, 1);
	lua_pushinteger(L, 2);
	lua_gettable(L, $input);
	float g = lua_tonumber(L, -1);
	lua_pop(L, 1);
	lua_pushinteger(L, 3);
	lua_gettable(L, $input);
	float b = lua_tonumber(L, -1);
	lua_pop(L, 1);
	
	float a = 1.0f;
	if (luaL_getn(L, $input) >= 4)
	{
		lua_pushinteger(L, 4);
		lua_gettable(L, $input);
		a = lua_tonumber(L, -1);
		lua_pop(L, 1);
	}
	
	// build the color
	$1 = Color(r, g, b, a);
}

%typecheck(SWIG_TYPECHECK_POINTER) Color
{
	bool naturalColor = false;
	void *ptr;
	if (SWIG_IsOK(SWIG_ConvertPtr(L,$input,(void**)&ptr,SWIGTYPE_p_Color,0))) 
	{
		$1 = 1;
		naturalColor = true;
	}
	
	
	if (!naturalColor)
	{
		if (lua_istable(L, $input) && (luaL_getn(L, $input) >= 3))
		{
			// verify that at least the first three elements of the table contain numbers
			lua_pushinteger(L, 1);
			lua_gettable(L, $input);
			int v1 = lua_isnumber(L, -1);
			lua_pop(L, 1);
			lua_pushinteger(L, 2);
			lua_gettable(L, $input);
			int v2 = lua_isnumber(L, -1);
			lua_pop(L, 1);
			lua_pushinteger(L, 3);
			lua_gettable(L, $input);
			int v3 = lua_isnumber(L, -1);
			lua_pop(L, 1);
			$1 = (v1 && v2 && v3);
		}
		else
		{
			$1 = 0;
		}
	}
}
#endif

class Color
{
public:
	float R, G, B, A;
	
	Color();
	Color(float r, float g, float b, float a=1.0f, bool clamp=true);
	Color FromInts(int r, int g, int b, int a=255, bool clamp=true);
	Color FromHexString(String hexString);
	
	bool operator==(const Color &c) const;
	bool operator!=(const Color &c) const;
	
	Color operator-(const Color &c) const;
	Color operator+(const Color &c) const;
	Color operator/(float divider) const;
	Color operator*(float scaleFactor) const;
};
