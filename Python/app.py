# -*- coding: utf-8 -*-
import dash
import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import Input, Output
import Pages

external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']

app = dash.Dash(__name__, external_stylesheets=external_stylesheets)

app.layout = html.Div(style={'backgroundColor': '#eceff1', 'margin': 0, 'boxShadow': '0 0 10px 0 rgba(0, 0, 0, 0.16)'},
                      children=[
    dcc.Tabs(id="tabs", value='tab-1', children=[
        dcc.Tab(label='Introduction', value='tab-1'),
        dcc.Tab(label='Structure', value='tab-2'),
        dcc.Tab(label='Field', value='tab-3'),
    ]),
    html.Div(id='tabs-content')
])

@app.callback(Output('tabs-content', 'children'),
              [Input('tabs', 'value')])
def render_content(tab):
    if tab == 'tab-1':
        return Pages.intro
    if tab == 'tab-2':
        return Pages.structure
    if tab == 'tab-3':
        return Pages.field


if __name__ == '__main__':
    app.run_server(debug=True)
