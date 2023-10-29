from flask import Flask, request
import asyncio
import g4f

g4f.debug.logging = True
app = Flask(__name__)

ans = "None"
que = ""

pmodel = None
prov = None

async def getResP(q):
    return g4f.ChatCompletion.create(
        model = pmodel,
        messages = [{"role": "user", "content": q}],
        provider = prov
    )

async def ask():
    global ans
    task = asyncio.create_task(getResP(que))
    ans = (await asyncio.gather(task))[0]

def getModel(mode):
	if mode == 0: return g4f.models.gpt_35_turbo
	else: return g4f.models.gpt_4

def getProvider(mode):
	if mode == 0: return g4f.Provider.AiAsk
	elif mode == 1: return g4f.Provider.MyShell
	elif mode == 2: return g4f.Provider.ChatBase
	elif mode == 3: return g4f.Provider.Phind
	else: return g4f.Provider.Yqcloud

@app.route('/', methods=["POST"])
def test():
	global que
	global pmodel
	global prov
	req = request.get_data().decode("utf-8")
	pmodel = getModel(int(req.split("#&x0S")[1]))
	prov = getProvider(int(req.split("#&x0S")[2]))
	que = "\n".join(req[5:].split("#&x0S")[3:])

	asyncio.run(ask())

	return ans

app.run(port=8000)