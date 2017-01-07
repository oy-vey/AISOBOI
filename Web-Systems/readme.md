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
	"links": {
			 "self" : "/films"
			},
    "films": [
                {
				"id": "00001",
                "name": "Fight Club",
				"director": "David Fincher",
                "year": 1994,
                "rating": "8.29",
				"links": {
							"self" : "/films/00001"
						 }
                },
                {
				"id": "00002",
                "name": "Brother",
				"director": "Aleksey Balabanov",
                "year": 1997,
                "rating": "7.79",
				"links": {
							"self" : "/films/00002"
						 }
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
	"links": {
				"self" : "/films/00003"
			 },
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
	"votes": [
			{
				"stars" : "One",
				"votes" : ["111","222"]
			},
			{
				"stars" : "Two" ,
				"votes" : ["333", "4444"]
			},
			{
				"stars" : "Three" ,
				"votes" : ["555"]
			},
			{
				"stars" : "Four" ,
				"votes" : ["666"]
			},
			{
				"stars" : "Five" ,
				"votes" : ["777", "888"]
			},
			{
				"stars" : "Six" ,
				"votes" : ["999"]
			},
			{
				"stars" : "Seven" ,
				"votes" : ["101", "102", "103"]
			},
			{
				"stars" : "Eight" ,
				"votes" : []
			},
			{
				"stars" : "Nine" ,
				"votes" : ["104", "105"]
			},
			{
				"stars" : "Ten" ,
				"votes" : ["106", "107", "108", "109", "110"]
			}
		]
			
}
```
#### 3. Rate film
##### Request:
POST /films/{id}/{rating}?user=111
##### Response:
- Code: Success - 200 HTTP_OK, Fail - 404 HTTP_NOT_FOUND

## Load Testing
### Параметры машины:
- Intel Core i5-4570
- 4GB RAM
- Ubuntu 16.04

### Запросы:
```
GET /films/
```
```
GET /films/{id}
```
### Сценарий:
Линейное увеличение до определенного уровня rps с последующей постоянной нагрузкой

[2000 rps](https://overload.yandex.net/6202)
Почти сразу наблюдается нехватка CPU, появляются HTTP и сетевые ошибки. Очевидно, что при такой нагрузке сервис не способен оперативно функционировать.

[1500 rps](https://overload.yandex.net/6203)
Нельзя сказать, что картина изменилась в лучшую сторону. Количество сетевых и HTTP ошибок уменьшилось, однако по прежнему наблюдается нехватка CPU. Имеет место волатильность для Response time distribution.

[1000 rps](https://overload.yandex.net/6205)
Полное отсутствие сетевых и HTTP ошибок. Почти на все запросы сервис отвечает менее чем за 4ms. Однако, загруженность CPU по прежнему высокая.

[800 rps](https://overload.yandex.net/6206)
Загруженность CPU на этом уровне составляет ~75-80%. Следовательно, можно считать данные уровень оптимальным.

