# *kebris-c & partner-login*

## Description

This repository contains a **cub3D skeleton** prepared to continue the mandatory
part in pairs.  
It is intentionally **not a full solution**: the structure is ready, parsing and
rendering entry points exist, and TODO sections mark what remains to implement.

Current state:
- Project name and build target changed from old `so_long` base to `cub3D`
- `.cub` extension flow wired in `main`
- Modular source layout for parser, validation, rendering, input and cleanup
- Basic placeholder rendering (ceiling/floor bands) to keep the loop testable
- Example `maps/example.cub` added

What is intentionally pending:
- Full mandatory parser robustness (all edge cases)
- Full map closure verification via flood-fill
- Full DDA raycasting and wall texturing
- Final collision/gameplay tuning

## Instructions

### Build

```bash
make
```

### Run

```bash
./cub3D maps/example.cub
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
