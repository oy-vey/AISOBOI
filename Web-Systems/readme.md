# Movies collection
Сервис представляет из себя коллекцию кинофильмов разных лет с возможностью оценивания понравившихся фильмов по шкале от 1 до 10. На основе пользовательских оценок формируется рейтинг кинофильмов.
## Approach (REST/RPC) grounding:
REST был выбран по следующим причинам:
- Cерверу не нужно состояние клиента;
- Концепции "CRUD" достаточно для взаимодействия с сервисом;
- REST пользуется популярностью, следовательно у сторонних разработчиков не составит проблем осуществить интеграцию с разрабатываемым сервисом; 
- REST предоставляет хорошие возможности для масштабируемости и расширяемости;

## API Description:
### Overview
- films/ 			# Films collection
- films/{id} 		# Specific Film
- films/{id}/{rating} # Rate specific film

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
#### 3. Rate film
##### Request:
POST /films/{id}/{rating}
##### Response:
CODE: 
- Success - 200 HTTP_OK
- Fail - 404 HTTP_NOT_FOUND