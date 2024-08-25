from hypercorn import Config
from hypercorn.asyncio import serve

from fastapi import FastAPI
from starlette.responses import FileResponse
from starlette.staticfiles import StaticFiles

app = FastAPI()
app.mount("/static", StaticFiles(directory="static"), name="static")


@app.get("/scott")
def scott():
    return FileResponse("static/scott.html")


if __name__ == "__main__":
    config = Config()
    config.bind = ["0.0.0.0:8012"]
    config.certfile = "../cert.pem"
    config.keyfile = "../key.pem"
    config.use_http2 = True

    import asyncio
    asyncio.run(serve(app, config))
