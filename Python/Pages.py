import dash
import dash_core_components as dcc
import dash_html_components as html

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
    html.H1('Visualizations of Electromagnetic Wave Scattering'),
    html.Div(style={'margin': 'auto', 'border': '0.5px solid #babdbe'}, children=[
        html.Div(style={'borderBottom': '0.5px solid #babdbe'}, children=[
            html.H6('Define Layered Structure'),
            html.P(
                'Enter number of layers and length, electric tensors, and magnetic tensors for each layer.'),
        ]),
        dcc.Input(placeholder='Number of Layers'),
        html.H6('Yo')])
])

field = html.Div(children=[
    html.H3('TODO: Field Page')
])
