# *kebris-c & kmarrero*

## Description

This repository contains a **cub3D** prepared to continue the mandatory
part in pairs.

## Instructions

### Build

```bash
make
```

### Run

```bash
./cub3D maps/valid.cub
```

### Expected map extension

The project expects map files using the **`.cub`** extension.

### Texture notes

For mandatory cub3D:
- Header identifiers: `NO`, `SO`, `WE`, `EA`
- Texture files should be `.xpm`
- In this skeleton, texture loading is left as a TODO module

### Suggested work split (2 people)

1. **Parser/validation owner**
   - Complete strict header parsing and error cases
   - Complete map validation and closed-map flood-fill
2. **Renderer owner**
   - Implement DDA raycasting
   - Add proper texture sampling and wall face selection
3. **Joint integration**
   - Hook parser output to renderer
   - Fix leaks and cleanup paths
   - Run invalid/valid map test matrix

## Resources

- cub3D subject PDF (mandatory requirements)
- Lode Vandevenne raycasting tutorial
- miniLibX Linux documentation

### AI usage note

We used AI assistance only for:
- project decomposition into phases/modules
- checklist-style planning
- skeleton bootstrap guidance

Final implementation, debugging, validation and submission criteria remain under
our responsibility.
