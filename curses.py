import curses

def main(stdscr):
    # Initialize curses
    curses.curs_set(0)  # Hide the cursor
    stdscr.nodelay(1)   # Make getch() non-blocking
    stdscr.timeout(100) # Refresh every 100ms

    # Initial position of the dragon
    x, y = 0, 0
    dragon = "GAGAN"

    # Main loop
    while True:
        stdscr.clear()
        try:
            stdscr.addstr(y, x, dragon)  # Draw the dragon
        except curses.error:
            pass  # Ignore errors if the terminal does not support the emoji
        stdscr.refresh()

        # Get user input
        key = stdscr.getch()

        # Move the dragon based on arrow keys
        if key == curses.KEY_UP and y > 0:
            y -= 1
        elif key == curses.KEY_DOWN and y < stdscr.getmaxyx()[0] - 1:
            y += 1
        elif key == curses.KEY_LEFT and x > 0:
            x -= 2  # Move 2 steps because emojis are wider
        elif key == curses.KEY_RIGHT and x < stdscr.getmaxyx()[1] - 2:
            x += 2  # Move 2 steps because emojis are wider
        elif key == ord('q'):  # Quit on 'q'
            break

# Run the program
curses.wrapper(main)