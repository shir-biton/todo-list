from fastapi import FastAPI, Response, Request

app = FastAPI()
@app.get("/set-cookie/{username}")
def set_cookie(response: Response, username: str):
    response.set_cookie(key="username", value=username)
    return {"message": "Cookie has been set"}

@app.get("/get-cookie")
def get_cookie(request: Request):
    username = request.cookies.get("username")
    if username:
        return {"message": f"Welcome back, {username}!"}
    else:
        return {"message": "No cookie found"}


if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="127.0.0.1", port=8003)
