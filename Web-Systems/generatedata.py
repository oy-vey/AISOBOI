import json


with open('Movies.json', 'r') as data_file:
    json_data = data_file.read()
data = json.loads(json_data)

id = 1
output = dict()
output_long = dict()
for input in data:
    # Collection
    output['id'] = str(id)
    output['name'] = input['name']
    output['director'] = input['director']
    output['year'] = input['year']
    output['links'] = {'self': 'films/' + str(id)}
    # Detailed
    output_long['id'] = str(id)
    output_long['name'] = input['name']
    output_long['director'] = input['director']
    output_long['year'] = input['year']
    output_long['links'] = {'self': 'films/' + str(id)}
    output_long['image'] = input['image']
    output_long['description'] = 'Description'
    output_long['actors'] = input['actors']
    output_long['votes'] = [{'Stars': 'One', 'Votes': []},
                            {'Stars': 'Two', 'Votes': []},
                            {'Stars': 'Three', 'Votes': []},
                            {'Stars': 'Four', 'Votes': []},
                            {'Stars': 'Five', 'Votes': []},
                            {'Stars': 'Six', 'Votes': []},
                            {'Stars': 'Seven', 'Votes': []},
                            {'Stars': 'Eight', 'Votes': []},
                            {'Stars': 'Nine', 'Votes': []},
                            {'Stars': 'Ten', 'Votes': []}]

    id += 1
    with open('MoviesCollection.json', 'a') as json_file:
        json_file.write(str(output) + ',\n')
    with open('MoviesDetailed.json', 'a') as json_file:
        json_file.write(str(output_long) + ',\n')
