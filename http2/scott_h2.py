import hypercorn
import uvicorn

from fastapi import FastAPI, HTTPException
from hypercorn import Config
from hypercorn.asyncio import serve
from pydantic import BaseModel
from typing import List, Optional

from starlette.responses import FileResponse
from starlette.staticfiles import StaticFiles

app = FastAPI()
app.mount("/static", StaticFiles(directory="static"), name="static")

@app.get("/scott")
def scott():
    return FileResponse("static/scott.html")


# Run the server with uvicorn
if __name__ == "__main__":
    config = Config()
    config.bind = ["0.0.0.0:8000"]  # Specify host and port
    config.certfile = "../cert.pem"
    config.keyfile = "../key.pem"
    config.use_http2 = True

    import asyncio
    asyncio.run(serve(app, config))
