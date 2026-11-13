# Source layout

Where the code lives, after the reorganization. File names are broadly correct guesses from what the code does; function and struct names are unchanged.

## Rules

- Each fragment (an overlay image loaded at run time) has a directory `src/fragments/<name>/` with one header `<name>.h`.
- Each resident source file `src/<file>.c` has one header `src/<file>.h`. Files split at fixed addresses (`<file>_2.c`, `<file>_3.c`, ...) share the header of `<file>.c`.
- Vendored libraries keep their own layout: `lib/ultralib` (libultra), and `src/libultra`, `src/libleo`, `src/libnaudio`, `src/libnumus`, `src/libgsm`.
- A function whose callers disagree on its prototype is declared locally in each caller, under "Declared here instead of in a header: the callers of these disagree on their types." Unifying those is annotation work, because it can change codegen.
- `docs/function-matches.csv` (column `source`) maps every function to its file.

## Fragments

| Fragment | Directory | Files | Functions | What it is (broad) |
|---|---|---|---|---|
| 000 | `src/fragments/audio_and_gb_emulator/` | 18 | 303 | N64 sound driver (synthesis, heap, sequence player) and the Game Boy emulator (CPU, APU, Transfer Pak) |
| 001 | `src/fragments/unidentified_001/` | 1 | 1 | not identified yet |
| 002 | `src/fragments/disk_error_screen/` | 1 | 9 | 64DD / disk error screen |
| 003 | `src/fragments/n64_logo/` | 1 | 5 | N64 logo intro |
| 004 | `src/fragments/gb_tower_team_prep/` | 1 | 4 | GB Tower team preparation |
| 005 | `src/fragments/battle_order_select/` | 1 | 33 | battle order selection |
| 006 | `src/fragments/cartridge_check/` | 2 | 40 | Game Boy cartridge check |
| 007 | `src/fragments/free_battle_setup/` | 5 | 108 | Free Battle setup and rental teams |
| 008 | `src/fragments/registration/` | 1 | 51 | team registration |
| 009 | `src/fragments/nintendo_cup_teams/` | 1 | 8 | Nintendo Cup '97 finalist teams |
| 010 | `src/fragments/pikachu_reward/` | 1 | 27 | Pikachu reward |
| 011 | `src/fragments/cup_select/` | 1 | 12 | cup selection |
| 012 | `src/fragments/battle/` | 98 | 2527 | battle engine, move animations, particles and COM AI |
| 013 | `src/fragments/vs_scene/` | 1 | 33 | VS screen before a battle |
| 014 | `src/fragments/main_menu/` | 2 | 33 | main menu |
| 015 | `src/fragments/lab_pc/` | 5 | 137 | Lab PC |
| 016 | `src/fragments/lab_pokemon_list/` | 11 | 163 | Lab Pokémon list |
| 017 | `src/fragments/lab_menu/` | 1 | 6 | Lab menu |
| 018 | `src/fragments/pokedex/` | 2 | 56 | Pokédex |
| 019 | `src/fragments/party_summary/` | 2 | 34 | party summary |
| 020 | `src/fragments/main_menu_launcher/` | 1 | 1 | launches the main menu |
| 021 | `src/fragments/launcher_relay_021/` | 1 | 1 | launcher relay |
| 022 | `src/fragments/launcher_relay_022/` | 1 | 1 | launcher relay |
| 023 | `src/fragments/launcher_relay_023/` | 1 | 1 | launcher relay |
| 024 | `src/fragments/launcher_relay_024/` | 1 | 1 | launcher relay |
| 025 | `src/fragments/fatal_error_screen/` | 1 | 6 | fatal error screen |
| 030 | `src/fragments/geo_model_030/` | 1 | 4 | geo layout callbacks for models |
| 031 | `src/fragments/particle_data/` | 2 | 8 | particle data |
| 032 | `src/fragments/geo_model_032/` | 1 | 9 | geo layout callbacks for models |
| 033 | `src/fragments/geo_model_033/` | 1 | 13 | geo layout callbacks for models |
| 034 | `src/fragments/geo_model_034/` | 1 | 8 | geo layout callbacks for models |
| 038 | `src/fragments/geo_model_038/` | 1 | 2 | geo layout callbacks for models |
| 039 | `src/fragments/geo_model_039/` | 1 | 1 | geo layout callbacks for models |
| 040 | `src/fragments/geo_model_040/` | 1 | 1 | geo layout callbacks for models |
| 106–258 | `src/fragments/model_data/` | 153 | 153 | model data, one file per fragment |

## Resident files

79 files in `src/`. Headers:

`asset_archive.h`, `audio_cache.h`, `audio_channel.h`, `audio_commands.h`, `audio_fade_helpers.h`, `audio_manager.h`, `audio_music.h`, `audio_sequence_queue.h`, `audio_sfx_wrapper.h`, `audio_sound_state.h`, `battle_hud.h`, `block_relocate.h`, `controller.h`, `crash_screen.h`, `debug_print.h`, `display_object_textures.h`, `dma.h`, `dp_intro.h`, `fabsf.h`, `font.h`, `game_state.h`, `gb_audio.h`, `gb_audio_render.h`, `gb_data.h`, `gb_mbc.h`, `gb_save.h`, `gb_tower.h`, `gb_tower_launch.h`, `geo_layout.h`, `geo_node.h`, `geo_render.h`, `gfx_buffer.h`, `gfx_rect.h`, `graphics_textures.h`, `hal_libc.h`, `input.h`, `jpeg_decoder.h`, `jpeg_stream.h`, `jpegutils.h`, `lab_item.h`, `leo.h`, `main.h`, `main_pool.h`, `matrix.h`, `memmap.h`, `memory.h`, `memory_main.h`, `menu.h`, `misc_stubs.h`, `model_animation_events.h`, `model_renderer.h`, `model_renderer_callbacks.h`, `model_vertex.h`, `model_vertex_draw.h`, `poke_icon.h`, `pokemon_lab_support.h`, `pokemon_stats.h`, `profiler.h`, `rom_device.h`, `rsp.h`, `save_data.h`, `scheduler.h`, `stage_loader.h`, `table_view.h`, `text_renderer.h`, `ui_graphics.h`, `util.h`, `vector_math.h`
