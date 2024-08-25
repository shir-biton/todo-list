# HTTP Protocol Presentation by Shir Biton and Michal Barer
## [Link to Google Slides](https://docs.google.com/presentation/d/1G04lyENYTNXnttITD_UTHmyX6ZvtQmTQ-09NqiFltG8/edit#slide=id.g2f24767dc3c_0_0)

# 1st Demo - todo server

## To run todo server
`python todo.py`

To run the server with TLS uncomment the lines 80-81 in todo.py and enter the following
PEM pass phrase:`shir` (and don't forget to change the client to use https).

## To compile todo_client.c
`gcc -o todo_client todo_client.c -Wall -lcurl`


## To run output
`./todo_client`


# 2st Demo - cookies

## To run cookie server
```bash
cd cookies
python cookie_server.py
```

## To compile cookie_client.c
`gcc -o cookie cookie_client.c -Wall -lcurl`


## To run output
`./cookie`

Make sure that you don't have the file `cookies.txt` in the same directory as the client, if you do, delete it.

## Check browser
Open browser and go to: `http://127.0.0.0:8003/set-cookie/{username}`, open Developer tools and check cookies and then go to:
`http://127.0.0.0:8003/get-cookie`

# 2st Demo - http1.1 vs http2

## To run cookie server
```bash
cd http2
python scott_h11.py
python scott_h2.py
```
(PEM pass phrase:shir)

## Check browser
Open browser and go to `https://0.0.0.0:8011/scott` for http1.1 and `https://0.0.0.0:8012/scott` for http2