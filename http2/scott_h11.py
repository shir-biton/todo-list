import uvicorn

from fastapi import FastAPI
from starlette.responses import FileResponse
from starlette.staticfiles import StaticFiles

app = FastAPI()
app.mount("/static", StaticFiles(directory="static"), name="static")

@app.get("/scott")
def scott():
    return FileResponse("static/scott.html")


if __name__ == "__main__":
    uvicorn.run(
        app,
        host="127.0.0.1",
        port=8001,
        ssl_keyfile="../key.pem",
        ssl_certfile="../cert.pem"
    )

