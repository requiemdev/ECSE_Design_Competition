from openai import OpenAI
import os

def openAiResponse(emotion, word):
    script_dir = os.path.dirname(os.path.abspath(__file__))
    prompt_path = os.path.join(script_dir, "prompt.txt")
    with open(prompt_path, "r") as f:
        prompt = f.read()

    client = OpenAI()
    try:
        response = client.responses.create(
            model="gpt-5-nano",
            input=f"{prompt}, {emotion}, {word}"
        )
        res = response.output_text
        print(res)
        return res
    except Exception as e:
        print(f"Error: {e}")
        return None

