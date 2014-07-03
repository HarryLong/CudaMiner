FILE(REMOVE_RECURSE
  "libdeviceQuery.cu.pdb"
  "libdeviceQuery.cu.a"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/deviceQuery.cu.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
