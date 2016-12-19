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

#### 1. Get list of films
##### Request:
GET /films/
##### Response:
`response.json`
```json
 {
    "films": [
                {
				"id": "00001",
                "name": "Fight Club",
                "year": 1994,
                "genre": ["DRAMA"],
                },
                {
				"id": "00002",
                "name": "Brother",
                "year": 1997,
                "genre": ["DRAMA","CRIME"],
                }
            ]
}
```
#### 2. Get specific film
##### Request:
GET /films/{id}
##### Response:
`response.json`
```json
{	"id": "00003",
    "name": "Knockin' on Heaven's Door",
    "year": 1997,
    "genre": ["DRAMA"],
    "rating": 8,
    "actors": [15, 16],
    "directors": [21]
}
```
#### 3. Get list of participants
##### Request:
GET /participants/
##### Response:
`response.json`
```json
{
    "participants": [
                        {
						"id": "00001",
                        "name": " Til",
                        "surname": "Schweiger",
                        "birth_date": "19-12-1963",
                        "death_date": null
                        },
                        {
						"id": "00002",
                        "name": "Jan Josef",
                        "surname": "Liefers",
                        "birth_date": "08-08-1964",
                        "death_date": null
                        }
                    ]
}
```
#### 4. Get specific participant
##### Request:
GET /participants/{id}
##### Response:
`response.json`
```json
{	
	"id": "00003",
    "name": "Johnny",
    "surname": "Depp",
    "birth_date": "09-06-1963",
    "death_date": null,
    "country_of_birth": "USA",
    "Biography": "Person's bio" 
}
```
