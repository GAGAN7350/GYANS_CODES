import curses

def main(stdscr):
    stdscr.clear()
    stdscr.addstr(0, 0, "Hello, world! Press any key to exit.")
    stdscr.refresh()
    stdscr.getch()  # Wait for a key press

curses.wrapper(main)