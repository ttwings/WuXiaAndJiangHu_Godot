---
name: "godot4-migration-check"
description: "Migrates Godot 3 GDScript to Godot 4 and verifies zero script errors. Invoke when fixing GDScript parse/compile errors or migrating MUD/game logic to Godot 4."
---

# Godot 4 Migration & Compile Check

Automates the repetitive work of migrating legacy GDScript (Godot 3 / C-style MUD) to Godot 4 and verifying the project compiles with zero script errors.

## When to Invoke

- Project reports `SCRIPT ERROR`, `Parse Error`, or `Compile Error` in Godot 4.
- Migrating Godot 3 scripts to Godot 4 API.
- Porting C-style MUD daemon/object files to GDScript.
- Need to confirm a Godot project has **0 script errors** before testing.

## Workflow

### 1. Locate Godot Binary

```bash
which godot godot4 2>/dev/null || find / -name "godot*" -type f 2>/dev/null | head
```

If missing, download the headless/server build:
```bash
curl -L -o /tmp/godot.zip "https://github.com/godotengine/godot/releases/download/4.3-stable/Godot_v4.3-stable_linux.x86_64.zip"
unzip -o /tmp/godot.zip -d /tmp/
```

### 2. Run Headless Compile Check

```bash
cd <project_root> && /tmp/Godot_v4.3-stable_linux.x86_64 --headless --quit 2>&1 | grep -E "SCRIPT ERROR|Parse Error|Compile Error"
```

To count errors:
```bash
... | grep -cE "SCRIPT ERROR|Parse Error|Compile Error"
```

**Note:** Resource errors (missing fonts/textures/tilesets) are NOT script errors — filter them out with:
```bash
grep -iE "error" | grep -viE "font|texture|resource|import|tile|autotile|loader|ext_resource|stex"
```

### 3. Isolate Per-Script Errors

When the project-level error is generic (`Could not parse global class "X"`), run the script directly to get the exact line:
```bash
godot --headless --script res://path/to/script.gd 2>&1 | head -20
```

### 4. Common Godot 3 → 4 Fixes (Apply Systematically)

#### A. Abstract Native Classes
| Godot 3 (broken) | Godot 4 (fix) |
|---|---|
| `DirAccess.new()` then `.open(path)` | `DirAccess.open(path)` returns instance directly |
| `File.new()` | `FileAccess.open(path, mode)` |

#### B. JSON API
| Godot 3 | Godot 4 |
|---|---|
| `JSON.parse(str).result` | `JSON.parse_string(str)` |
| `JSON.print(data)` | `JSON.stringify(data, indent)` |

#### C. Method Name Collisions (Godot 4 forbids same-named var/func or parent signature mismatch)

- `set(key, value)` conflicts with `Object.set(StringName, Variant)`.
  **Fix:** rename to `set_attr(key, value)` across **all** call sites (use regex replace, exclude `set_xxx` methods).
- `weight()` function conflicts with `weight` variable.
  **Fix:** rename function to `query_total_weight()`.
- `this_object(ob=self)` conflicts with built-in.
  **Fix:** define `func this_object(): return self` (no params) in base class; add `func this_player(): return self` too.

#### D. Removed APIs
| Removed | Replacement |
|---|---|
| `OS.get_time()` | `Time.get_unix_time_from_system()` |
| `ease()` | `erase()` (for dict key removal) |

#### E. Autoload Requirements
Autoload scripts **must** `extends Node`. Add `extends Node` to daemon scripts (e.g., `CHINESE_D.gd`).

#### F. Class Name Resolution in Headless
`class_name` types may not resolve when running `--quit`. Use `preload("res://path/Type.gd")` as a const for cross-script type checks instead of `is Type`.

### 5. Batch Rename Safely (Python)

```python
import os, re
for root, dirs, files in os.walk('inherit'):  # add more dirs
    for f in files:
        if not f.endswith('.gd'): continue
        p = os.path.join(root, f)
        s = open(p).read()
        o = s
        s = re.sub(r'\.set\(', '.set_attr(', s)               # .set( → .set_attr(
        s = re.sub(r'(?<![_a-zA-Z0-9])set\(', 'set_attr(', s)  # bare set( → set_attr(
        if s != o: open(p, 'w').write(s)
```
Always exclude third-party `addons/` directories.

### 6. Re-verify Until Zero

Repeat step 2 until the error count is `0`. Resource import errors (fonts, textures, .stex) are acceptable — they only mean assets haven't been imported in the editor yet.

## Verification Criteria

- `grep -cE "SCRIPT ERROR|Parse Error|Compile Error"` returns **0**.
- No autoload instantiation failures (all autoloads extend Node).
- No `Could not parse global class` errors.
