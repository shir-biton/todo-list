import uvicorn

from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from typing import List, Optional

app = FastAPI()


class Task(BaseModel):
    id: int
    title: str
    description: Optional[str] = None
    completed: bool = False

class TaskUpdate(BaseModel):
    title: Optional[str] = None
    description: Optional[str] = None
    completed: Optional[bool] = None


tasks: List[Task] = []


def find_task(task_id: int) -> Task:
    for task in tasks:
        if task.id == task_id:
            return task
    return None


@app.post("/tasks", response_model=Task)
def create_task(task: Task):
    if find_task(task.id):
        raise HTTPException(status_code=400, detail="Task with this ID already exists.")
    tasks.append(task)
    return task


@app.get("/tasks", response_model=List[Task])
def get_tasks():
    return tasks


@app.get("/tasks/{task_id}", response_model=Task)
def get_task(task_id: int):
    task = find_task(task_id)
    if not task:
        raise HTTPException(status_code=404, detail="Task not found.")
    return task


@app.patch("/tasks/{task_id}", response_model=Task)
def update_task(task_id: int, task: TaskUpdate):
    stored_task = find_task(task_id)
    if not stored_task:
        raise HTTPException(status_code=404, detail="Task not found.")

    stored_task.title = task.title or stored_task.title
    stored_task.description = task.description or stored_task.description
    stored_task.completed = task.completed if task.completed is not None else stored_task.completed

    return stored_task


@app.delete("/tasks/{task_id}", status_code=204)
def delete_task(task_id: int):
    global tasks
    task = find_task(task_id)
    if not task:
        raise HTTPException(status_code=404, detail="Task not found.")
    tasks = [t for t in tasks if t.id != task_id]


if __name__ == "__main__":
    uvicorn.run(
        app,
        host="127.0.0.1",
        port=8002,
        # ssl_keyfile="key.pem",  # Uncomment to enable HTTPS
        # ssl_certfile="cert.pem"
    )
