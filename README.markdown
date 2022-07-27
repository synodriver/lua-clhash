# lua-clhash
```lua
local clhash = require("clhash")

local key = clhash.get_random_key(1,2)
print(clhash.hash(key,"asjakda"))
print(clhash.hash(key,"asjakda"))
print(clhash.hash(key,"asjakd"))
print(clhash.hash(key,"asjakddad"))
print(clhash.hash(key,"asjakddad"))
clhash.free_key(key)
```