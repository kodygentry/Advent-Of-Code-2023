# part 1
def calculate_points(card_data):
    # Split the data into winning numbers and numbers you have
    winning_numbers, your_numbers = card_data.split(" | ")
    winning_numbers = set(winning_numbers.split())
    your_numbers = your_numbers.split()

    # Check for matches and calculate points
    matches = 0
    for num in your_numbers:
        if num in winning_numbers:
            matches += 1

    # Calculate points based on matches
    return 2 ** (matches - 1) if matches > 0 else 0

def process_scratchcards(file_path):
    total_points = 0
    with open(file_path, 'r') as file:
        for line in file:
            card_points = calculate_points(line.strip())
            total_points += card_points

    return total_points

# Path to the file
file_path = 'input.txt'

# Calculate and print the total points
total_points = process_scratchcards(file_path)
print("Total points:", total_points)

# part 2
def count_matches(winning_numbers, your_numbers):
  return sum(num in winning_numbers for num in your_numbers)

def process_scratchcards(file_path):
  with open(file_path, 'r') as file:
      cards = [line.strip() for line in file]

  total_cards = len(cards)
  card_counts = [1] * total_cards  # Initialize count for each card

  for i in range(total_cards):
      winning_numbers, your_numbers = cards[i].split(" | ")
      winning_numbers = set(winning_numbers.split())
      your_numbers = your_numbers.split()

      matches = count_matches(winning_numbers, your_numbers)

      # Add copies of subsequent cards based on the number of matches
      for j in range(i + 1, min(i + 1 + matches, total_cards)):
          card_counts[j] += card_counts[i]

  return sum(card_counts)

# Path to the file
file_path = 'input.txt'

# Calculate and print the total number of scratchcards
total_scratchcards = process_scratchcards(file_path)
print("Total scratchcards:", total_scratchcards)