import os

sprite_path = 'resources/Sprites'
animation_path = 'resources/Animations'

output_file = open('resources.txt', 'w')

for r, d, f in os.walk(sprite_path):
    for file in f:
        if file.lower().endswith('.png'):
            output_file.write(os.path.join(r, file) + '\n')
