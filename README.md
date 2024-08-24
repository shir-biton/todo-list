# 1st Demo - todo server

## To run todo server
`python todo.py`
(PEM pass phrase:shir)

## To compile todo_client.c
`gcc -o todo_client todo_client.c -Wall -lcurl`


## To run output
`./todo_client`


# 2st Demo - cookies

## To run cookie server
`python cookie_server.py`
(PEM pass phrase:shir)

## To compile cookie_client.c
`gcc -o cookie cookie_client.c -Wall -lcurl`


## To run output
`./cookie`

## Check browser
Open browser and go to `http://127.0.0.0:8003` open Developer tools and check cookies

# 2st Demo - http1.1 vs http2

## To run cookie server
`cd http2`
`python scott_h11.py`
`python scott_h2.py`
(PEM pass phrase:shir)

## Check browser
Open browser and go to `https://0.0.0.0:8001` for http1.1 and `https://0.0.0.0:8000` for http2