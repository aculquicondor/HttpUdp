from flask import Flask, request
app = Flask(__name__)

@app.route("/", methods=['GET', 'POST'])
def hello():
    name = 'World'
    if request.method == 'POST':
        name = request.form.get('name', 'World')
    return '''
<h1>Hello {name}!</h1>
<form method="post">
<input type="text" name="name">
<button type="submit">Hello!</button>
</form>
    '''.format(name=name)

if __name__ == "__main__":
    app.run()
