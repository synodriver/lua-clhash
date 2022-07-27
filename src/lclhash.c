#include <stdlib.h>
#include <stdint.h>

#include "lua.h"
#include "lauxlib.h"

#include "clhash.h"

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#elif
#define DLLEXPORT
#endif /* _WIN32 */


static int
lget_random_key(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have 2 seeds");
    }
    uint64_t seed1 = (uint64_t) luaL_checkinteger(L, 1);
    uint64_t seed2 = (uint64_t) luaL_checkinteger(L, 2);
    void *key = get_random_key_for_clhash(seed1, seed2);
    if (key == NULL)
    {
        return luaL_error(L, "get null key");
    }
    lua_pushlightuserdata(L, key);
    return 1;
}

static int
lfree_key(lua_State* L)
{
    if (lua_gettop(L) != 1)
    {
        return luaL_error(L, "must have a key as void*");
    }
    if(lua_type(L,1)!=LUA_TLIGHTUSERDATA)
    {
        return luaL_error(L, "key must be void*");
    }
    void* key = lua_touserdata(L,1);
    free_key(key);
    return 0;
}


static int
lhash(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must have a key and data to hash");
    }
    if(lua_type(L,1)!=LUA_TLIGHTUSERDATA && lua_type(L,1)!=LUA_TSTRING)
    {
        return luaL_error(L, "key must be void* or string");
    }
    void* key=NULL;
    if(lua_type(L,1)==LUA_TLIGHTUSERDATA)
    {
        key = lua_touserdata(L,1);
    }
    else
    {
        key = (void*)lua_tostring(L,1);
    }
    size_t size;
    const char*  data = luaL_checklstring(L, 2, &size);
    uint64_t h = clhash(key, data, size);
    lua_pushinteger(L, (lua_Integer)h);
    return 1;
}

static luaL_Reg lua_funcs[] = {
        {"get_random_key", &lget_random_key},
        {"free_key",     &lfree_key},
        {"hash",     &lhash},
        {NULL, NULL}
};

DLLEXPORT int luaopen_clhash(lua_State *L)
{
    luaL_newlib(L, lua_funcs);
    return 1;
}