# ♟ Console Chess Game (C++)

A console-based chess game built in C++, featuring full move validation, time control modes, and save/load support — all in the Windows terminal.

---

## 🎮 Features

-  Full chess rules (castling, promotion, en passant, checkmate, etc.)
-  Time control modes:
  - Normal (10 min/player)
  - Blitz (5 min/player)
  - Add Time (3 min + increment)
  - No Time
-  Save & load game state to/from file
-  Windows-only console interface with Unicode chess pieces
-  Supports board flipping and last move tracking

---

##  Project Structure

```plaintext
├── Game.h / Game.cpp         # Game loop, timing, save/load
├── Board.h / Board.cpp       # Board setup, piece movement
├── Piece.h + subclasses      # Base piece and derived classes: Pawn, King, Queen, etc.
├── Commands.h / Commands.cpp # Command handling and move validation
├── Symbols.h                 # Unicode chess symbols
├── Saves.txt                 # Save file for game state
