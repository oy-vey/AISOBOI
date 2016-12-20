# Movies collection
Сервис представляет из себя коллекцию кинофильмов разных лет с возможностью оценивания понравившихся фильмов по шкале от 1 до 10. На основе пользовательских оценок формируется индивидуальный рейтинг кинофильма.
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
- Content-Type: application/json
- Code: 200 HTTP_OK
- Body `response.json`
```json
 {
    "films": [
                {
				"id": "00001",
                "name": "Fight Club",
				"director": "David Fincher",
                "year": 1994,
                "rating": "8.29"
                },
                {
				"id": "00002",
                "name": "Brother",
				"director": "Aleksey Balabanov",
                "year": 1997,
                "rating": "7.79",
                }
            ]
}
```
#### 2. Get specific film
##### Request:
GET /films/{id}
##### Response:
- Content-Type: application/json
- Code: Success - 200 HTTP_OK, Fail - 404 HTTP_NOT_FOUND
- Body `response.json`
```json
{	
	"id": "00003",
    "name": "Forrest Gump",
	"director": "Robert Zemeckis",
    "year": 1994,
    "rating": "7.29",
    "image": "http://filmaster.pl/thumbnail/?path=img%2Fobj%2Ff%2Fb2%2F38%2Fforrest-gump.jpg&crop=center&size=180",
    "description": "Movie description",
	"actors": [
            "Tom Hanks",
            "Robin Wright",
            "Gary Sinise",
            "Mykelti Williamson",
            "Sally Field",
            "Rebecca Williams",
            "Michael Conner Humphreys",
            "Harold G. Herthum",
            "George Kelly",
            "Bob Penny"
        ],
	"votes": {
			"1" : 3,
			"2" : 7,
			"3" : 11,
			"4" : 1,
			"5" : 34,
			"6" : 56,
			"7" : 123,
			"8" : 312312,
			"9" : 8576586,
			"10" : 321321,
		}
			
}
```
#### 3. Rate film
##### Request:
POST /films/{id}/{rating}
##### Response:
- Code: Success - 200 HTTP_OK, Fail - 404 HTTP_NOT_FOUND
