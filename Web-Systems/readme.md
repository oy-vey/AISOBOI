# Movies collection

## Approach (REST/RPC) grounding:
REST был выбран по следующим причинам:
- Cерверу не нужно состояние клиента;
- Концепции "CRUD" достаточно для взаимодействия с сервисом;
- REST пользуется популярностью, следовательно у сторонних разработчиков не составит проблем осуществить интеграцию с разрабатываемым сервисом; 
- REST предоставляет хорошие возможности для масштабируемости и расширяемости;

## API Description:
### Entities
- films/ 			# Films collection
- films/{id} 		# Specific Film
- participants/ 	# Participants collection (Actor/Director/Producer/Screenwriter)
- participant/{id}	# Specific participant

### Queries

#### Get list of films
##### Request
GET films/
##### Response
            		  {
                        "films": [
                          {
                            "name": "Fight Club",
                            "year": 1994,
                            "genre": ["DRAMA"],
                            "rating": 8.8,
                            "actors": [1, 3, 6],
                            "directors": [2]
                          },
                          {
                            "name": "Brother",
                            "year": 1997,
                            "genre": ["DRAMA","CRIME"],
                            "rating": 8,
                            "actors": [7, 9, 11],
                            "directors": [4]
                          }
                        ]
                      }


