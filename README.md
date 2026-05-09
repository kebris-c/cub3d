*This project has been created as part of the 42 curriculum by kebris-c, kmarrero.*

## Description

**cub3D** is a 42 School project: a small first-person view of a maze, inspired by *Wolfenstein 3D*, implemented in C. The program reads a scene description from a **`.cub`** file (textures, floor/ceiling colors, and a 2D map), validates the data, then uses **raycasting** (DDA) and **miniLibX** to draw textured walls in real time.

This repository is a **pair implementation** of the mandatory cub3D scope: parsing and map checks, player movement and rotation, raycasting, XPM wall textures for the four cardinal directions, and a clean shutdown path. Sample maps live under `maps/good/` and `maps/bad/` for manual regression.

## Instructions

### Prerequisites

- **OS:** Linux (the Makefile builds **miniLibX for Linux** under `minilibx-linux/`).
- **Toolchain:** `cc` (or `gcc`), `make`.
- **System libraries** (names vary by distro): X11, Xext, zlib, and the math library — e.g. on Debian/Ubuntu you typically need development packages such as `libx11-dev`, `libxext-dev`, and `zlib1g-dev` so linking with `-lX11 -lXext -lz -lm` succeeds.

### Compilation

From the repository root:

```bash
make
```

This builds **libft**, **miniLibX**, object files under `objs/`, and the **`cub3D`** binary. Rebuild from scratch:

```bash
make re
```

Remove objects and the binary:

```bash
make fclean
```

### Execution

The program expects **exactly one** argument: a path to a map file whose name ends with **`.cub`**.

```bash
./cub3D maps/good/play_subject_reference.cub
```

Other examples:

```bash
./cub3D maps/good/play_min.cub
./cub3D maps/good/play_large_box.cub
```

### Controls

| Key | Action |
|-----|--------|
| W / S | Move forward / backward |
| A / D | Strafe left / right |
| Left / Right arrow | Rotate |
| Escape | Quit |

Close the window to exit as well.

### Map and assets

- Scene files use the **`.cub`** extension (enforced at startup).
- Header keys follow the subject: **`NO`**, **`SO`**, **`WE`**, **`EA`** for wall textures; textures are loaded from **`.xpm`** paths as given in the map.
- Source layout: **`src/entry/`** (`main`), **`src/parser/`** (`.cub` text and map grid), **`src/map_check/`** (rules + BFS enclosure from spawn), **`src/raycast/`** (DDA + per-frame column pass), **`src/render/`** (ceiling/floor + textured walls), **`src/setup/`** (MLX + player from spawn), **`src/player_motion/`**, **`src/input/`**, **`src/files/`**, **`src/runtime/`** (signals + teardown), **`src/helpers/`** (colors, pixels, walkability); shared API in **`include/cub3d.h`**.

## Resources

- **42 cub3D subject** — official mandatory and bonus requirements (evaluation criteria, map rules, allowed functions).
- **Lode's Computer Graphics Tutorial — Raycasting** by Lode Vandevenne: [Raycasting](https://lodev.org/cgtutor/raycasting.html) — classic step-by-step explanation of grid-based raycasting and DDA.
- **miniLibX** — 42’s simple X11 windowing library; see the headers and `man` pages under `minilibx-linux/man/` in this tree, and your campus MLX documentation for the authoritative API list allowed by the subject.

### Use of AI tools

AI assistance was used only for **non-substitutive** support, for example:

- **README and documentation:** structuring this file, aligning wording with 42 README expectations, and summarizing build/run steps.
- **Planning:** high-level task breakdown, checklists, and suggested module ownership when working in pairs.

**Parsing, validation, raycasting, rendering, movement, memory management, debugging, and evaluation readiness** were done and verified by the authors. Any AI-generated suggestion was reviewed, adapted, or rejected before entering the graded codebase.
