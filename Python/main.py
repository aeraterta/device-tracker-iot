from fastapi import FastAPI
from controllers.routes import router

app = FastAPI()

app.include_router(router)

@app.get("/test")
async def root():
    return {"message": "Hello World"}