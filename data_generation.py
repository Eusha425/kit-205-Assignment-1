import random
import string

# Generate playlists and songs with names "playlist_a" to "playlist_z" and "song_a" to "song_z"
playlists = [f"playlist_{char}" for char in string.ascii_lowercase]
songs = [f"song_{char}" for char in string.ascii_lowercase]

# Function to generate random data
def generate_data(num_entries):
    data = []
    for _ in range(num_entries):
        entry = f"1\n{random.choice(playlists)}\n{random.choice(songs)}\n"
        data.append(entry)
    data.append("0")
    return data

# Number of entries to generate
num_entries = 100000

# Generate data
generated_data = generate_data(num_entries)

# Specify the output file name
output_file = "generated_data.txt"

# Write the generated data to the file
with open(output_file, "w") as file:
    file.writelines(generated_data)

print(f"Generated data has been written to {output_file}")
