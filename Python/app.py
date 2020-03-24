# -*- coding: utf-8 -*-
import dash
import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import Input, Output
import itertools

external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']

WIDTH = '200px'

# Pages
intro = html.Div(style={'display': 'flex', 'flexDirection': 'row', 'padding': 'auto', 'margin': '10px'}, children=[
    html.Div(children=[
        dcc.Markdown('''#### Introduction '''),
        dcc.Markdown('''The development of this graphical user interface was supported by grant DMS-1411393 (2014-2018) from the National Science Foundation at Louisiana State University under the guidance of PI Stephen P. Shipman. As one of the projects covered by the grant, undergraduate students created the mathematical code and web interface to compute and simulate harmonic electromagnetic fields in layered media. The goal is to make available to the community a versatile online application for the computation of EM fields in media with any number of layers having arbitrary electric and magnetic tensors. The objectives are(1) to allow scientists to explore phenomena of scattering, guided modes, and resonance in the most general EM layered media and (2) to provide a pedagogical tool for students and professionals to learn EM in layered media. The project is in its initial stages and is being further developed by undergraduate students through various funding sources, including President’s Aid from Louisiana State University. Further developments include a tutorial on the theory of electrodynamics in layered media, a user manual, computation of transmission and reflection coefficients as functions of frequency and angle of incidence, and computation of dispersion relations for pure and leaky guided modes.'''),
    ]),
    html.Div(style={'width': '2500px', 'padding': 'auto', 'marginLeft': '50px'},
             children=[
                 dcc.Markdown('''#### Credits '''),
        html.Ul(children=[
            html.A(style={'textDecoration': 'none', 'color': 'black'}, href='https://www.math.lsu.edu/~shipman/', children=[
                html.H6(
                    '''Stephen Shipman '''),
                html.P('''Professor, Mathematics''')]),
            html.A(style={'textDecoration': 'none', 'color': 'black'}, children=[
                html.H6(
                    '''Dylan Blanchard '''),
                html.P('''Web Developer''')]),
            html.A(style={'textDecoration': 'none', 'color': 'black'}, children=[
                html.H6(
                    '''Joshua Brock '''),
                html.P('''Math Backend''')]),
            html.A(style={'textDecoration': 'none', 'color': 'black'}, children=[
                html.H6(
                    ''' Andrew Rogers '''),
                html.P('''Math Backend''')]),
            html.A(style={'textDecoration': 'none', 'color': 'black'}, children=[
                html.H6(
                    ''' Trevor Gilmore '''),
                html.P('''Mathbox 3D Field Visualization''')]),
            html.A(style={'textDecoration': 'none', 'color': 'black'}, href='https://noahtemplet.dev/', children=[
                html.H6(
                    '''Noah Templet '''),
                html.P('''Web Developer''')]),
            html.A(style={'textDecoration': 'none', 'color': 'black'}, children=[
                html.H6(
                    '''Michael Sheppard III '''),
                html.P('''Web Developer''')])]),
        html.A(href='http://emlab.utep.edu/ee5390cem.htm', children=[
            html.P('Computational Electromagnetics (Additional Information)')]),
        html.A(href='https://www.math.lsu.edu/~shipman/articles/ShipmanWelters2013a.pdf', children=[
            html.P('EM Scattering Publication')])
    ])]
)

structure = html.Div(children=[
    html.H2('Visualizations of Electromagnetic Wave Scattering'),
    html.Div(style={'margin': 'auto', 'border': '0.5px solid #babdbe'}, children=[
        html.Div(style={'borderBottom': '0.5px solid #babdbe'}, children=[
            html.H4(style={'fontWeight': 'bold'}, children=['Define Layered Structure']),
            html.P(
                'Enter number of layers and length, electric tensors, and magnetic tensors for each layer.'),
        ]),
        html.Div(style={'display': 'flex', 'flexDirection': 'row', 'alignItems': 'center', 'padding': 'auto', 'margin': 'auto'}, children=[
            html.H5(style={'paddingRight': '50px'}, children=['Number of Layers: ']),
            dcc.Input(id='num_layers', type='number', value=3, min=1),
        ]),
        html.Span(style={'display': 'grid', 'gridGap': '50px', 'gridTemplateColumns': '200px', 'margin': 'auto', 'padding': 'auto'}, children=[
                html.H6(style={'gridColumnStart': 2, 'gridColumnEnd': 3, 'fontWeight': 500}, children=['LENGTH']),
                html.H6(style={'gridColumnStart': 3, 'gridColumnEnd': 4, 'fontWeight': 500}, children=['EPSILON']),
                html.H6(style={'gridColumnStart': 4, 'gridColumnEnd': 5, 'fontWeight': 500}, children=['MU'])
            ]),
        html.Div(id='layers', style={'margin': '10px', 'padding': 'auto'}),
        html.Button(id='build', children=['Build Structure'], style={'margin': '20px'}),
        html.Span(id='structure')])
])

field = html.Div(children=[
    html.H3('TODO: Field Page')
])


app = dash.Dash(__name__, external_stylesheets=external_stylesheets)

app.title = 'EMWS'

app.layout = html.Div(style={'backgroundColor': '#eceff1', 'margin': 0, 'boxShadow': '0 0 10px 0 rgba(0, 0, 0, 0.16)'},
                      children=[
    dcc.Tabs(id="tabs", value='tab-1', children=[
        dcc.Tab(label='Introduction', value='tab-1'),
        dcc.Tab(label='Structure', value='tab-2'),
        dcc.Tab(label='Field', value='tab-3'),
    ]),
    html.Div(id='tabs-content')
])

app.config.suppress_callback_exceptions=True

# Callback for rendering tabs
@app.callback(Output('tabs-content', 'children'),
              [Input('tabs', 'value')])
def render_content(tab):
    if tab == 'tab-1':
        return intro
    if tab == 'tab-2':
        return structure
    if tab == 'tab-3':
        return field

# Callback for building the layered structure
@app.callback(Output('layers', 'children'),
              [Input('num_layers', 'value')])
def check_layers(num):
    layers = ['Ambient Left']
    children = []
    for n in range(num-2):
        layers.append('Layer ' + str(n+1))
    if num > 1:
        layers.append('Ambient Right')
    for layer in layers:
        i = layers.index(layer)
        children.append(html.Div(style={'display': 'grid', 'gridGap': '50px', 'gridTemplateColumns': WIDTH, 'minHeight': '200px', 'margin': '10px', 'padding': 'auto'}, children=[
            html.P(style={'gridColumnStart': 1, 'gridColumnEnd': 2}, children=[
                layer]),
            html.Div(style={'gridColumnStart': 2, 'gridColumnEnd': 3, 'display': 'flex', 'justifyContent': 'center', 'width': WIDTH}, children=[
                dcc.Input(type='number', value=10, id='length'+str(i))
            ]),
            html.Div(style={'gridColumnStart': 3, 'gridColumnEnd': 4, 'display': 'grid', 'width': WIDTH}, children=[
                html.Div(style={'display': 'grid', 'gridGap': '5px', 'width': '25px', 'height': '25px'}, children=[
                    dcc.Input(id=str(i)+'e11', value=1.5, style={'width': '50px', 'gridColumnStart': 1, 'gridColumnEnd': 2, 'gridRowStart': 1, 'gridRowEnd': 2}), dcc.Input(id=str(i)+'e12', value=0, style={'width': '50px', 'gridColumnStart': 2, 'gridColumnEnd': 3, 'gridRowStart': 1, 'gridRowEnd': 2}), dcc.Input(id=str(i)+'e13', value=0, style={'width': '50px', 'gridColumnStart': 3, 'gridColumnEnd': 4, 'gridRowStart': 1, 'gridRowEnd': 2}),
                    dcc.Input(id=str(i)+'e21', value=0, style={'width': '50px', 'gridColumnStart': 1, 'gridColumnEnd': 2, 'gridRowStart': 2, 'gridRowEnd': 3}), dcc.Input(id=str(i)+'e22', value=8, style={'width': '50px', 'gridColumnStart': 2, 'gridColumnEnd': 3, 'gridRowStart': 2, 'gridRowEnd': 3}), dcc.Input(id=str(i)+'e23', value=0, style={'width': '50px', 'gridColumnStart': 3, 'gridColumnEnd': 4, 'gridRowStart': 2, 'gridRowEnd': 3}),
                    dcc.Input(id=str(i)+'e31', value=0, style={'width': '50px', 'gridColumnStart': 1, 'gridColumnEnd': 2, 'gridRowStart': 3, 'gridRowEnd': 4}), dcc.Input(id=str(i)+'e32', value=0, style={'width': '50px', 'gridColumnStart': 2, 'gridColumnEnd': 3, 'gridRowStart': 3, 'gridRowEnd': 4}), dcc.Input(id=str(i)+'e33', value=1, style={'width': '50px', 'gridColumnStart': 3, 'gridColumnEnd': 4, 'gridRowStart': 3, 'gridRowEnd': 4}),
                ])
            ]),
            html.Div(style={'gridColumnStart': 4, 'gridColumnEnd': 5, 'display': 'grid', 'width': WIDTH}, children=[
                html.Div(style={'display': 'grid', 'gridGap': '5px', 'width': '25px', 'height': '25px'}, children=[
                    dcc.Input(id=str(i)+'u11', value=4, style={'width': '50px', 'gridColumnStart': 1, 'gridColumnEnd': 2, 'gridRowStart': 1, 'gridRowEnd': 2}), dcc.Input(id=str(i)+'u12', value=0, style={'width': '50px', 'gridColumnStart': 2, 'gridColumnEnd': 3, 'gridRowStart': 1, 'gridRowEnd': 2}), dcc.Input(id=str(i)+'u13', value=0, style={'width': '50px', 'gridColumnStart': 3, 'gridColumnEnd': 4, 'gridRowStart': 1, 'gridRowEnd': 2}),
                    dcc.Input(id=str(i)+'u21', value=0, style={'width': '50px', 'gridColumnStart': 1, 'gridColumnEnd': 2, 'gridRowStart': 2, 'gridRowEnd': 3}), dcc.Input(id=str(i)+'u22', value=1, style={'width': '50px', 'gridColumnStart': 2, 'gridColumnEnd': 3, 'gridRowStart': 2, 'gridRowEnd': 3}), dcc.Input(id=str(i)+'u23', value=0, style={'width': '50px', 'gridColumnStart': 3, 'gridColumnEnd': 4, 'gridRowStart': 2, 'gridRowEnd': 3}),
                    dcc.Input(id=str(i)+'u31', value=0, style={'width': '50px', 'gridColumnStart': 1, 'gridColumnEnd': 2, 'gridRowStart': 3, 'gridRowEnd': 4}), dcc.Input(id=str(i)+'u32', value=0, style={'width': '50px', 'gridColumnStart': 2, 'gridColumnEnd': 3, 'gridRowStart': 3, 'gridRowEnd': 4}), dcc.Input(id=str(i)+'u33', value=1, style={'width': '50px', 'gridColumnStart': 3, 'gridColumnEnd': 4, 'gridRowStart': 3, 'gridRowEnd': 4}),
                ])
            ])
        ]))
    return children

#Callback for building structure on button click
@app.callback(Output('structure', 'children'),
            [Input('layers', 'children'),
            Input('build', 'n_clicks')])
def build_structure(layers, n):
    tot_length = 0
    for layer in layers:
        # print(layer['props']['children'][1]['props']['children'][0]['props']['value'])
        tot_length += layer['props']['children'][1]['props']['children'][0]['props']['value']
    left_ambient = -layers[0]['props']['children'][1]['props']['children'][0]['props']['value']
    fig = {
        'layout': {
            'title': 'Layered Structure',
            'xaxis': {'autorange': False, 'range': [left_ambient, tot_length+left_ambient], 'visible': True, 'constraint': 'range', 'showLine': True},
            'yaxis': {'visible': False, 'showLine': True}
        }
    }
    return dcc.Graph(config={'displaylogo': False, 'staticPlot': True}, figure=fig)

if __name__ == '__main__':
    app.run_server(debug=True)

