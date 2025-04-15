# Function to check for snake or ladder
def check_snake_or_ladder(position, snakes, ladders):
    if position in snakes:
        print(f"Oops! A snake! Went down from {position} to {snakes[position]}")
        return snakes[position]
    elif position in ladders:
        print(f"Yay! A ladder! Went up from {position} to {ladders[position]}")
        return ladders[position]
    return position

# Function to play the game
def play_game():
    num_players = 2  # 2 players
    player_positions = [0] * num_players  # Initialize player positions to 0
    snakes = {16: 6, 47: 26, 49: 11, 56: 53, 62: 19, 64: 60, 87: 24, 93: 73, 95: 75, 98: 78}
    ladders = {1: 38, 4: 14, 9: 31, 21: 42, 28: 84, 36: 44, 51: 67, 71: 91, 80: 100}

    turn = 0  # Player 1 starts the game

    while True:
        print(f"\nPlayer {turn + 1}'s turn")

        # Player inputs their dice roll
        while True:
            try:
                roll = int(input(f"Player {turn + 1}, enter your dice roll (1-6): "))
                if 1 <= roll <= 6:
                    break
                else:
                    print("Please enter a valid number between 1 and 6.")
            except ValueError:
                print("Invalid input! Please enter a number between 1 and 6.")

        print(f"Player {turn + 1} rolled a {roll}")

        # Move the player, but don't let them exceed position 100
        new_position = player_positions[turn] + roll
        if new_position > 100:
            print(f"Player {turn + 1} can't move past position 100. Staying at position {player_positions[turn]}")
        else:
            player_positions[turn] = new_position
            print(f"Player {turn + 1} moves to position {player_positions[turn]}")

        # Check for snake or ladder
        player_positions[turn] = check_snake_or_ladder(player_positions[turn], snakes, ladders)

        # Check if the player reached the finish line
        if player_positions[turn] >= 100:
            print(f"\nPlayer {turn + 1} wins the game!")
            break

        # Switch turn to the next player
        turn = (turn + 1) % num_players

# Entry point of the program
if __name__ == "__main__":
    print("Welcome to the Snake and Ladders Game!")
    play_game()
