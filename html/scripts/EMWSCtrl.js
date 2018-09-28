// code style: https://github.com/johnpapa/angular-styleguide 
angular.module('myApp', []).controller('EMWSCtrl', function($scope) {






        google.charts.load('current', { packages: ['corechart'] });
        $scope.context;
        $scope.NumLayers = 5;
        $scope.o = 1; //omega
        $scope.k1 = 0;
        $scope.k2 = 0;
        $scope.wLeft = -5; //bounds for the transmission graph
        $scope.wRight = 5;
        $scope.incoming = [1, 0, 0, 0];
        $scope.eArray = [];
        $scope.muArray = [];
        $scope.lArray = [];
        $scope.totalLength = 0;
        $scope.outputModes;
        $scope.mBack1x; 
        $scope.mBack1y;
        $scope.mBack2x;
        $scope.mBack2y;
        $scope.mFor1x;
        $scope.mFor1y;
        $scope.mFor2x;
        $scope.mFor2y;
        $scope.crystal;
        $scope.field;
        $scope.dispersion;

        $scope.Layers = [{
                "layerName": "Ambient Left",
                "epsilon": [1, 2, 3, 4],
                "epsilonA": [[1, 0, 0], [0, 1, 0], [0, 0, 1]],
                "mu": [1, 2, 3, 4],
                "muA": [[1,0,0],[0,1,0], [0, 0, 1]],
                "length": 6
            },
            {
                "layerName": "Layer 1",
                "epsilon": [2, 2, 3, 6],
                "epsilonA": [[2, 1, 0], [1, 2, 0], [0, 0, 1]],
                "mu": [2, 2, 3, 6],
                "muA": [[1,0,0],[0,1,0], [0, 0, 1]],
                "length": 6
            },
            {
                "layerName": "Layer 2",
                "epsilon": [2, 2, 3, 6],
                "epsilonA": [[3, 0, 0], [0, 3, 0], [0, 0, 1]],
                "mu": [2, 2, 3, 6],
                "muA": [[1,0,0],[0,1,0], [0, 0, 1]],
                "length": 9
            },
            {
                "layerName": "Layer 3",
                "epsilon": [2, 2, 3, 6],
                "epsilonA": [[2, 1, 0], [1, 2, 0], [0, 0, 1]],
                "mu": [2, 2, 3, 6],
                "muA": [[1,0,0],[0,1,0], [0, 0, 1]],
                "length": 6
            },
            {
                "layerName": "Ambient Right",
                "epsilon": [1, 2, 3, 4],
                "epsilonA": [[1, 0, 0], [0, 1, 0], [0, 0, 1]],
                "mu": [1, 2, 3, 4],
                "muA": [[1,0,0],[0,1,0], [0, 0, 1]],
                "length": 6
            },
        ];

        // $scope.
        $scope.init = function() {       
            getArrays();
            updateAll();
            google.charts.setOnLoadCallback(createStructureChart);
            google.charts.setOnLoadCallback(createFieldChart);
            //google.charts.setOnLoadCallback(createDispersionChart);
            //google.charts.setOnLoadCallback(createTransmissionChart);
            createAnim();
            //printDispersionChart("dispView", "100%", "100%");
            
            //$(".p2").css("visibility", "hidden");



            //$(".p1").addClass("ng-hide");

        }

        function addHide() {
            // $(".p2").addClass("ng-hide");
            // $(".p3").addClass("ng-hide");
            // $('.p2').css('visibility', 'visible');
            // $('.p3').css('visibility', 'visible');
        }

        $scope.addLayer = function() {
            // getIncomingMode();
            $scope.Layers[$scope.NumLayers - 1].layerName = ("Layer " + ($scope.NumLayers - 1)); //Renames last ambient right layer 
            $scope.NumLayers++;
            $scope.Layers.push({
                "layerName": "Ambient Right",
                "epsilon": [1, 2, 3, 4],
                "epsilonA": [[1, 0, 0], [0, 1, 0], [0, 0, 1]],
                "mu": [1, 2, 3, 4],
                "muA": [[1, 0, 0], [0, 1, 0], [0, 0, 1]],
                "length": 6
            })
        };

        $scope.removeLayer = function() {
            $scope.Layers.pop();
            $scope.NumLayers--;
            $scope.Layers[$scope.NumLayers - 1].layerName = ("Ambient Right");
        }

        $scope.printLengths = function() {
            angular.forEach($scope.Layers, function(value, index) {

                console.log("length" + value.length);
            })
        }

        $scope.updateLayers = function() {
            if ($scope.NumLayers == null || $scope.NumLayers == 0) { console.log("scope is null or 0"); } else if ($scope.NumLayers > $scope.Layers.length) {
                if ($scope.Layers[$scope.NumLayers - 1]) {
                    $scope.Layers[$scope.NumLayers - 1].layerName = 
                            ("Layer " + ($scope.NumLayers - 1)); } 
                else 
                    $scope.Layers[$scope.Layers.length - 1].layerName = 
                        ("Layer " + ($scope.Layers.length - 1));
                if ($scope.NumLayers - 2 == 0) {
                    $scope.Layers[$scope.NumLayers - 2].layerName = "Ambient Left"; }
                $scope.Layers.push({
                    "layerName": "Ambient Right",
                    "epsilon": [1, 2, 3, 4],
                    "epsilonA": [[1, 0, 0], [0, 1, 0], [0, 0, 1]],
                    "mu": [1, 2, 3, 4],
                    "muA": [[1, 0, 0], [0, 1, 0], [0, 0, 1]],
                    "length": 6
                })
                if ($scope.NumLayers > $scope.Layers.length)
                    $scope.updateLayers();
            } else if ($scope.NumLayers < $scope.Layers.length) {
                $scope.Layers.pop();
                $scope.Layers[$scope.NumLayers - 1].layerName = ("Ambient Right");
                if ($scope.NumLayers < $scope.Layers.length)
                    $scope.updateLayers();
            }
        }
        
        $scope.buildStruct = function() {
            getArrays();
            updateCrystal();
            createStructureChart();
        }

        $scope.buildModes = function() {
            updateModes();
        }
        
        //#########################################################################################
        //#########################################################################################
        //#########################################################################################
        //#########################################################################################
        //#########################################################################################


        $scope.runExp = function() {
            $("canvas").remove();
            getArrays();
            updateAll();
            createFieldChart();
            createAnim();
            //$scope.buildFieldsWithAnim();
        };
        
        function getArrays() {
            $scope.totalLength = 0;
            for (var layer in $scope.Layers){
                $scope.eArray[layer] = ($scope.Layers[layer].epsilonA);
                $scope.muArray[layer] = ($scope.Layers[layer].muA);
                $scope.lArray[layer] = parseFloat($scope.Layers[layer].length);
                $scope.totalLength += parseFloat($scope.Layers[layer].length);
            }
            
        }

        function updateModes() {
            var lastEigensystem = $scope.crystal.Struct.Eigensystems.length - 1;
            $scope.mBack1x = parseFloat(math.re($scope.crystal.Struct.Eigensystems[lastEigensystem][0].eigenvalue).toFixed(9));
            $scope.mBack1y = parseFloat(math.im($scope.crystal.Struct.Eigensystems[lastEigensystem][0].eigenvalue).toFixed(9));
            $scope.mBack2x = parseFloat(math.re($scope.crystal.Struct.Eigensystems[lastEigensystem][1].eigenvalue).toFixed(9));
            $scope.mBack2y = parseFloat(math.im($scope.crystal.Struct.Eigensystems[lastEigensystem][1].eigenvalue).toFixed(9));
            $scope.mFor1x = parseFloat(math.re($scope.crystal.Struct.Eigensystems[0][2].eigenvalue).toFixed(9));
            $scope.mFor1y = parseFloat(math.im($scope.crystal.Struct.Eigensystems[0][2].eigenvalue).toFixed(9));
            $scope.mFor2x = parseFloat(math.re($scope.crystal.Struct.Eigensystems[0][3].eigenvalue).toFixed(9));
            $scope.mFor2y = parseFloat(math.im($scope.crystal.Struct.Eigensystems[0][3].eigenvalue).toFixed(9));
        }
        
        function updateCrystal(){
            var k = [$scope.k1,$scope.k2,$scope.o];
            $scope.crystal = emScattering2.Driver(
                    $scope.eArray,$scope.muArray,$scope.lArray,$scope.NumLayers,k,$scope.incoming);
            };
            
        function updateFields(){
            $scope.field = $scope.crystal.determineField();
        }
        
        
        function updateAll(){
            updateCrystal();
            updateFields();
            updateModes();
        }
            
        function createFieldChart() {
            var fields = $scope.field;
            var interfaces = $scope.crystal.materialInterfaces();

            var data = new google.visualization.DataTable();
            data.addColumn('number', 'z');
            //data.addColumn('number', document.getElementById("shownVal").value);
            data.addColumn('number', 'Eₓ');
            data.addColumn('number', 'Eᵧ');
            data.addColumn('number', 'Hₓ');
            data.addColumn('number', 'Hᵧ');
            
            //Iterate through fields values

            for (var i = 0, N = fields.z.length; i < N; i++) {
                /*
                if (document.getElementById("shownVal").value == 'Eₓ') {
                    data.addRows([
                        [fields.z[i], fields.Ex[i]]
                    ]);
                }
                if (document.getElementById("shownVal").value == 'Eᵧ') {
                    data.addRows([
                        [fields.z[i], fields.Ey[i]]
                    ]);
                }
                if (document.getElementById("shownVal").value == 'Hₓ') {
                    data.addRows([
                        [fields.z[i], fields.Hx[i]]
                    ]);
                }
                if (document.getElementById("shownVal").value == 'Hᵧ') {
                    data.addRows([
                        [fields.z[i], fields.Hy[i]]
                    ]);
                }
                */
                data.addRows([
                    [fields.z[i], fields.Ex[i], fields.Ey[i], fields.Hx[i], fields.Hy[i]]
                ]);

                // console.log(fields.z[i] + " " + fields.Ex[i] + " " + fields.Ey[i] + " " + fields.Hx[i] + " " + fields.Hy[i]);
            }

            var options = {
                chart: {
                    title: document.getElementById("shownVal").value + ' Values in Relation to Z'
                },
                hAxis: {
                     
                },
                width: "100%",
                height: "100%",
                chartArea: {
                    left: 40,
                    top: 40
                }

            };

            function printInterfaces(dataTable) { //prints the colored squares on the top of the chart
                var cli = this.getChartLayoutInterface();
                var chartArea = cli.getChartAreaBoundingBox();
                var cols = ['red', 'orange', 'yellow', 'green', 'blue', 'purple'];
                var w = cli.getXLocation(interfaces[1]) - cli.getXLocation(interfaces[0]);
                var y = cli.getChartAreaBoundingBox().height;
                // console.log(interfaces);
                // console.log("w:" + w);
                // console.log("y:" + y);
                // console.log("gety:" + Math.floor(cli.getYLocation(1)));
                // console.log("bounding:" + cli.getChartAreaBoundingBox().top);
                var yBound = cli.getChartAreaBoundingBox().top;
              
                var htmlClass = "addHere"; //confusing set of addHere variables. Essentially, they were set up originally to allow for me to add the same chart to two different places. 
                                            //Will work to remove in the next couple weeks.
                if (htmlClass == "addHere2")
                    $(".overlay2").remove();
                else if (htmlClass == "addHere")
                    $(".overlay").remove();
                else if (htmlClass == "addHere3")
                    $(".overlay3").remove();
                for (var i = 0; i < interfaces.length - 1; i++) {
                    var w = cli.getXLocation(interfaces[i + 1]) - cli.getXLocation(interfaces[i]);

                    // document.getElementsByClassName('overlay' + i).remove();
                    addStruct(htmlClass, i, cols[i % 5], w, y);
                    
                    // document.querySelector('.overlay').style.position = 'absolute';
                    // document.querySelector('.overlay').style.opacity = '.5';
                    // document.querySelector('.overlay').style.top = Math.floor(cli.getChartAreaBoundingBox().top) + "px";
                    // document.querySelector('.overlay').style.left = Math.floor(cli.getXLocation(interfaces[i])) + 15 + "px";

                };

                if (htmlClass == "addHere") {
                    var overlays = document.querySelectorAll('.overlay');
                    for (var j = 0; j < overlays.length; j++) {
                        overlays[j].style.position = 'absolute';
                        overlays[j].style.opacity = '.5';
                        overlays[j].style.top = Math.floor(cli.getChartAreaBoundingBox().top) + 65 + "px";
                        overlays[j].style.left = Math.floor(cli.getXLocation(interfaces[j])) + 16 + "px";

                    }
                } else if (htmlClass == "addHere2") {
                    var overlays = document.querySelectorAll('.overlay2');
                    for (var j = 0; j < overlays.length; j++) {
                        overlays[j].style.position = 'absolute';
                        overlays[j].style.opacity = '.5';
                        overlays[j].style.top = Math.floor(cli.getChartAreaBoundingBox().top) + 15 + "px";
                        overlays[j].style.left = Math.floor(cli.getXLocation(interfaces[j])) + 30 + "px";
                    }
                }



            }

            var chart = new google.visualization.LineChart(document.getElementById('structView'));
            google.visualization.events.addListener(chart, 'ready', printInterfaces.bind(chart, data)); //all from Google's tutorial https://developers.google.com/chart/interactive/docs/overlays
            //var chart = new google.charts.Line(document.getElementById('linechart_material'));
            chart.draw(data, options);

            var myElements = document.querySelectorAll(".hiddenChart");
            for (var i = 0; i < myElements.length; i++) {
                myElements[i].style.opacity = 1;
            }

            var chartView = new google.visualization.DataView(data);

            $scope.toggleEx = function() {
                chartView.hideColumns([1]);
                chart.draw(chartView, options);
            }
    
            $scope.toggleEy = function() {
                chartView.hideColumns([2]);
                chart.draw(chartView, options);
            }
    
            $scope.toggleHx = function() {
                chartView.hideColumns([3]);
                chart.draw(chartView, options);
            }
    
            $scope.toggleHy = function() {
                chartView.hideColumns([4]);
                chart.draw(chartView, options);
            }

            $scope.resetFieldChart = function() {
                chartView.setColumns([0, 1, 2, 3 , 4]);
                chart.draw(chartView, options);
            }
        }

        function createAnim() {
            var eXmax = 1;
            var hXmax = 1;
            var endRange = $scope.totalLength;
            var canvasElement = "testcanvas";
            var interfaces = $scope.crystal.materialInterfaces();
            var elem = document.getElementById(canvasElement);
            var jelem = $("#" + canvasElement);
            var rgbColor = jelem.parent().css("background-color");
            var WIDTH = elem.offsetWidth;
            var HEIGHT = elem.offsetHeight;
            var w1 = WIDTH;
            var h1 = HEIGHT;
            var three = THREE.Bootstrap({
                plugins: ['core', 'controls'],
                controls: {
                    klass: THREE.OrbitControls
                },
                size: {
                    width: w1,
                    height: h1,
                },
            });            
            var renderer = three.renderer;
            var scene = three.scene;
            var camera = three.camera;
            // Insert into document
            elem.appendChild(renderer.domElement);
            // MathBox $scope.context
            $scope.context = new MathBox.Context(renderer, scene, camera).init();
            var mathbox = $scope.context.api;
            // Set size
            renderer.setSize(WIDTH, HEIGHT);
            $scope.context.resize({ viewWidth: WIDTH, viewHeight: HEIGHT });
            // Place camera and set background
            camera.position.set(-1, 2, 4);
            renderer.setClearColor(new THREE.Color(rgbColor), 1.0);
            var view = mathbox
                .set({
                    focus: 3,
                })
                .cartesian({
                    range: [
                        [0, endRange],
                        [-eXmax, eXmax],
                        [-hXmax, hXmax]
                    ],
                    scale: [2, 2, 2],
                });

            view.axis({
                detail: 30,
            });

            view.axis({
                axis: 2,
            });

            view.scale({
                divide: 10,
            })
            view.ticks({
                classes: ['foo', 'bar'],
                width: 2
            });

            view.scale({ //adds "X-Axis" to the graph
                divide: 1,
                origin: [0, -2, 0, 0],
                axis: "x",
            }).text({
                live: false,
                data: ["Electric Field"]
            }).label({
                color: 0x0074D9,
                offset: [75, 20]
            })

            view.scale({ //adds "Y-Axis" to the graph
                divide: 1,
                origin: [0, 0, 2, 0],
                axis: "y",
            }).text({
                live: false,
                data: ["Magnetic Field"]
            }).label({
                color: 0xFF4136,
                offset: [80, 20]
            })

            view.grid({
                    axes: "xy",
                    divideX: endRange,
                    divideY: 10
                }) //makes two axes in space
                .grid({
                    axes: "xz",
                    divideX: endRange,
                    divideY: 10,
                })

            var colorCoords = []; //possibly remove, replace with just applying interfaces to arrays
            var cols = ['red', 'orange', 'yellow', 'green', 'blue', 'purple'];
            for (var i = 0; i < interfaces.length - 1; i++) {
                var array1 = [ //only x changes on all shapes coordinates
                    //seperate 1st and last arrays. also, make each array part of an array[][]                    
                    0 + interfaces[0 + i], -2, 0, 0 + interfaces[1 + i], -2, 0, 0 + interfaces[1 + i], 2, 0, 0 + interfaces[0 + i], 2, 0, //first column
                ];
                var array2 = [0 + interfaces[0 + i], 0, 2, 0 + interfaces[0 + i], 0, -2, 0 + interfaces[1 + i], 0, -2, 0 + interfaces[1 + i], 0, 2, ];
                view.voxel({
                    data: array1,
                    width: 4,
                    height: 2,
                    depth: 1,
                    items: 4,
                    channels: 3,
                });

                view
                    .transform({
                        pass: 'eye',
                        position: [0, 0, 0],
                        scale: [1, 1, 1],
                    })
                    .face({
                        color: cols[i % 5],
                        width: 3,
                        line: false,
                        shaded: true,
                        opacity: .3,
                        zOrder: 9,
                    })
                    .face({
                        color: cols[i % 5],
                        width: 3,
                        fill: false,
                        opacity: .3,
                        zOrder: 9,
                    })
                    .array({
                        data: [0, 0, 0],
                        channels: 3,
                    })
                view.voxel({
                    data: array2,
                    width: 4,
                    height: 2,
                    depth: 1,
                    items: 4,
                    channels: 3,
                });

                view
                    .transform({
                        pass: 'eye',
                        position: [0, 0, 0],
                        scale: [1, 1, 1],
                    })
                    .face({
                        color: cols[i % 5],
                        width: 3,
                        line: false,
                        shaded: true,
                        opacity: .3,
                        zOrder: 9,
                    })
                    .face({
                        color: cols[i % 5],
                        width: 3,
                        fill: false,
                        line: true,
                        opacity: .3,
                        zOrder: 9,
                    })
                    .array({
                        data: [0, 0, 0],
                        channels: 3,
                    })
            }


            var runsetup = true;
            var E1,E2,H1,H2;
            view.interval({
                id: 'ElectricFieldPlot',
                width: endRange * 10, //fields.Ex.length,
                expr: function(emit, z, i, t) {
                    if(z<=endRange){
                    if (runsetup) {
                        E1 = $scope.crystal.mathboxSetupEf();
                    };                    
                    E2 = $scope.crystal.mathboxEf($scope.crystal.Struct.lengths,t,z,E1.ExR,E1.ExPhi,E1.EyR,E1.EyPhi);
                    emit(z, E2.Ex, E2.Ey);
                    emit(z, 0, 0);
                    }
                },
                items: 2,
                channels: 3,
                live: true,
            });
            view.vector({
                points: '#ElectricFieldPlot',
                color: 0x0074D9,
                width: 1,
                start: true,
            });

            view.interval({
                id: 'MagneticFieldPlot',
                width: endRange * 10, //fields.Ex.length,
                expr: function(emit, z, i, t) {
                    if(z <= endRange){
                    if (runsetup) {
                        H1 = $scope.crystal.mathboxSetupHf();
                        runsetup = false;
                    };
                    H2 = $scope.crystal.mathboxHf($scope.crystal.Struct.lengths,t,z,H1.HxR,H1.HxPhi,H1.HyR,H1.HyPhi);
                    emit(z, H2.Hx, H2.Hy);
                    emit(z, 0, 0);
                    }
                },
                items: 2,
                channels: 3,
                live: true,
            });

            view.vector({
                points: '#MagneticFieldPlot',
                color: 0xFF4136,
                width: 1,
                start: true,
            });
            var visible = false;
            var madeVisible = false;
            var frame = function() {
                var parentVisibility = jelem.parent().css("visibility");
                    //console.log("doings things: ");
                if(parentVisibility != 'hidden'){
                    requestAnimationFrame(frame);
                    visible = true;
                    
                }
                else if(parentVisibility == 'hidden'){
                    visible = false;

                    requestAnimationFrame(frame);
                    renderer.domElement.style.visibility = parentVisibility;
                    return;
                }
                
                if(!madeVisible) {
                    renderer.domElement.style.visibility = parentVisibility; //wheretohide
                    madeVisible = true;
                }
                

                if(!visible)
                renderer.setSize(WIDTH, HEIGHT);
                $scope.context.frame();
                renderer.render(scene, camera);
                rgbColor = jelem.parent().css("background-color"); //0xFF851B;
                renderer.setClearColor(new THREE.Color(rgbColor), 1.0);
            };
            requestAnimationFrame(frame);
        }

        
 
        //#########################################################################################
        //#########################################################################################
        //#########################################################################################
        //#########################################################################################
        //#########################################################################################
        
        
        $scope.buildTransmission = function() {
            create2DArrays();
            updateCrystal();
            createTransmissionChart();
        }

        function createTransmissionChart() {
            var omegLow = 0; //document.getElementById("oLow").value; //hardcode
            var omegHigh = 5; //document.getElementById("oHi").value; //hardcode
            var kZsList = [1, 2, 3];
            // var kZs = document.getElementById("kzList").value;
            // for(var i = 0; i < kZs.length; i++) {
            //  console.log(kZs.charAt(i));
            //  if(isNumeric(kZs.charAt(i))) {
            //    var str = ""+kZs.charAt(i);
            //    kZsList.push(parseInt(str));
            //  }
            // }
            var divName = "transmissionView";
            console.log(kZsList);
            var transmissionGraph = $scope.crystal.transmission(kZsList, $scope.k1, $scope.k2, $scope.wLeft, $scope.wRight, 100);
            var data = new google.visualization.DataTable();
            data.addColumn('number', 'omega');
            for (var i = 0; i < transmissionGraph.kzList.length; i++) {
                data.addColumn('number', 'kz' + transmissionGraph.kzList[i]);
            }
            var dataArray = new Array(transmissionGraph.omegaRange.length);
            for (var i = 0; i < dataArray.length; i++) {
                dataArray[i] = new Array(transmissionGraph.kzList.length);
            }

            for (var i = 0; i < transmissionGraph.omegaRange.length; i++) {
                dataArray[i][0] = transmissionGraph.omegaRange[i];
                for (var j = 1; j <= transmissionGraph.kzList.length; j++) {
                    dataArray[i][j] = transmissionGraph.transmissionCoeffArrays[j - 1][i];
                }
            }


            for (var i = 0; i < dataArray.length; i++) {
                data.addRows([
                    dataArray[i]
                ]);
            }
            var options = {
                chart: {
                    title: 'transmission graph'
                },
                chartArea: {
                    left: 40,
                    top: 5
                },
                width: '100%',
                height: '100%'
            };

            var chart = new google.visualization.LineChart(document.getElementById(divName));

            chart.draw(data, options);
            console.log(dataArray[0][1]);

            var myElements = document.querySelectorAll(".hiddenChart1");
            for (var i = 0; i < myElements.length; i++) {
                myElements[i].style.opacity = 1;
            }
        }

        function _createAnim_DEPRECATED() {
            var eXmax = 1;
            var hXmax = 1;
            var endRange = $scope.totalLength;
            var canvasElement = "testcanvas";
            var crystal1 = $scope.crystal;
            var fields = $scope.field;
            var epsilon = $scope.epsilon2D;
            var mu = $scope.mu2D;
            var interfaces = $scope.crystal.materialInterfaces();
            var elem = document.getElementById(canvasElement);
            var jelem = $("#" + canvasElement);
            console.log("canvas element jquer:" + jelem.parent().css("background-color"));
            var rgbColor = jelem.parent().css("background-color");
            var WIDTH = elem.offsetWidth;
            var HEIGHT = elem.offsetHeight;
            var w1 = WIDTH;
            var h1 = HEIGHT;
            var three = THREE.Bootstrap({
                plugins: ['core', 'controls'],
                controls: {
                    klass: THREE.OrbitControls
                },
                size: {
                    width: w1,
                    height: h1,
                    // left: "400",
                },
            });
            // expect(three.renderer.domElement.style.visibility).toBe('hidden');

            var renderer = three.renderer;
            var scene = three.scene;
            var camera = three.camera;
            // renderer.domElement.style.visibility = 'hidden';

            console.log("styling canvas elem");
            // Insert into document

            elem.appendChild(renderer.domElement);

            // MathBox $scope.context
            $scope.context = new MathBox.Context(renderer, scene, camera).init();
            var mathbox = $scope.context.api;
            // mathbox2 = mathBox({
            //   plugins: ['core', 'controls', 'cursor'],
            //   controls: {
            //     klass: THREE.OrbitControls
            //   },    });
            // mathbox.install('controls');
            // Set size
            renderer.setSize(WIDTH, HEIGHT);
            $scope.context.resize({ viewWidth: WIDTH, viewHeight: HEIGHT });

            // Place camera and set background
            camera.position.set(-1, 2, 4);
            renderer.setClearColor(new THREE.Color(rgbColor), 1.0);
            // renderer.domElement.style.visibility = 'hidden';

            console.log("made it here too");
            var view = mathbox
                .set({
                    focus: 3,
                })
                .cartesian({
                    range: [
                        [0, endRange],
                        [-eXmax, eXmax],
                        [-hXmax, hXmax]
                    ],
                    scale: [2, 2, 2],
                });

            view.axis({
                detail: 30,
            });

            view.axis({
                axis: 2,
            });

            view.scale({
                divide: 10,
            })
            view.ticks({
                classes: ['foo', 'bar'],
                width: 2
            });

            // view.grid({
            //   divideX: 30,
            //   width: 1,
            //   opacity: 0.5,
            //   zBias: -5,
            // });
            view.scale({ //adds "X-Axis" to the graph
                divide: 1,
                origin: [0, -2, 0, 0],
                axis: "x",
            }).text({
                live: false,
                data: ["Electric Field"]
            }).label({
                color: 0x0074D9,
                offset: [75, 20]
            })

            view.scale({ //adds "Y-Axis" to the graph
                divide: 1,
                origin: [0, 0, 2, 0],
                axis: "y",
            }).text({
                live: false,
                data: ["Magnetic Field"]
            }).label({
                color: 0xFF4136,
                offset: [80, 20]
            })

            view.grid({
                    axes: "xy",
                    divideX: endRange,
                    divideY: 10
                }) //makes two axes in space
                .grid({
                    axes: "xz",
                    divideX: endRange,
                    divideY: 10,
                })

                // three.canvas.style.visibility = "hidden";

            var colorCoords = []; //possibly remove, replace with just applying interfaces to arrays
            var cols = ['red', 'orange', 'yellow', 'green', 'blue', 'purple'];
            for (var i = 0; i < interfaces.length - 1; i++) {
                var array1 = [ //only x changes on all shapes coordinates

                    //seperate 1st and last arrays. also, make each array part of an array[][]
                    //
                    0 + interfaces[0 + i], -2, 0, 0 + interfaces[1 + i], -2, 0, 0 + interfaces[1 + i], 2, 0, 0 + interfaces[0 + i], 2, 0, //first column
                    //0+interfaces[0+i], 0, 1, 0+interfaces[0+i], 0, -1, 0+interfaces[1+i], 0, -1, 0+interfaces[1+i], 0, 1,  //first row
                    // 0+interfaces[interfaces.length-2], -1, 0, 0+interfaces[interfaces.length-1], -1, 0, 0+interfaces[interfaces.length-1], 1, 0, 0+interfaces[interfaces.length-2], 1, 0, //last column
                    // 0+interfaces[interfaces.length-2], 0, 1, 0+interfaces[interfaces.length-2], 0, -1, 0+interfaces[interfaces.length-1], 0, -1, 0+interfaces[interfaces.length-1], 0, 1,  //last row


                ];
                var array2 = [0 + interfaces[0 + i], 0, 2, 0 + interfaces[0 + i], 0, -2, 0 + interfaces[1 + i], 0, -2, 0 + interfaces[1 + i], 0, 2, ]

                // colorCoords.push(array1); //remove push, place the voxel code here
                // colorCoords.push(array2);?
                console.log("test array1:" + array1)
                view.voxel({
                    data: array1,
                    width: 4,
                    height: 2,
                    depth: 1,
                    items: 4,
                    channels: 3,
                });

                view
                    .transform({
                        pass: 'eye',
                        position: [0, 0, 0],
                        scale: [1, 1, 1],
                    })
                    .face({
                        color: cols[i % 5],
                        width: 3,
                        line: false,
                        shaded: true,
                        opacity: .3,
                        zOrder: 9,
                    })
                    .face({
                        color: cols[i % 5],
                        width: 3,
                        fill: false,
                        opacity: .3,
                        zOrder: 9,
                    })
                    .array({
                        data: [0, 0, 0],
                        channels: 3,
                    })
                view.voxel({
                    data: array2,
                    width: 4,
                    height: 2,
                    depth: 1,
                    items: 4,
                    channels: 3,
                });

                view
                    .transform({
                        pass: 'eye',
                        position: [0, 0, 0],
                        scale: [1, 1, 1],
                    })
                    .face({
                        color: cols[i % 5],
                        width: 3,
                        line: false,
                        shaded: true,
                        opacity: .3,
                        zOrder: 9,
                    })
                    .face({
                        color: cols[i % 5],
                        width: 3,
                        fill: false,
                        line: true,
                        opacity: .3,
                        zOrder: 9,
                    })
                    .array({
                        data: [0, 0, 0],
                        channels: 3,
                    })
            }

            var ourFunc;
            var runsetup = true;
            var EigVals = new Array();
            var EigVecs = new Array();
            var ExrArray = new Array();
            var ExthetaArray = new Array();
            var EyrArray = new Array();
            var EythetaArray = new Array();

            // var HxrArray = new Array();
            // var HxthetaArray = new Array();
            // var HyrArray = new Array();
            // var HythetaArray = new Array();

            view.interval({
                id: 'ElectricFieldPlot',
                width: endRange * 10, //fields.Ex.length,
                expr: function(emit, z, i, t) {
                    if (runsetup) {
                        var U = crystal1.scattering($scope.o, $scope.k1, $scope.k2, $scope.incoming);
                        //Electric field
                        var cxE = [$scope.incoming[0], $scope.incoming[1], U.x[0], U.x[1]];
                        var cyE = [0, 0, U.y[0], U.y[1]];
                        var cE = new numeric.T(cxE, cyE);
                        
                        //Magnetic field
                        // var cxH = [j1, j2, U.x[2], U.x[3]];
                        // var cyH = [0, 0, U.y[2], U.y[3]];
                        // var cH = new numeric.T(cxH, cyH);

                        for (var q = 0; q < epsilon.length; q++) {
                            EigVals[q] = emScattering.eigenvaluesIsotropic(epsilon[q], mu[q], $scope.k1, $scope.k2);
                            EigVecs[q] = emScattering.eigenvectorsIsotropic(epsilon[q], mu[q], $scope.k1, $scope.k2);
                            
                            // console.log("EigVecs[q]: "+EigVecs[q].y[0][0]);//EigVecs[layernum].y[wavetype][vectornum]
                            // .x or .y for real and imaginary parts
                            // wavetype is 0 for ex, 1 for ey, 2 for hx, 3 for hy
                            // Electric field
                            var ExR = new Array();
                            var ExTheta = new Array();
                            var EyR = new Array();
                            var EyTheta = new Array();
                            // Magnetic field
                            // var HxR = new Array();
                            // var HxTheta = new Array();
                            // var HyR = new Array();
                            // var HyTheta = new Array();
                            for (var j = 0; j < 4; j++) {
                                //Electric field
                                var ExA = cE.x[j] * EigVecs[q].x[0][j];
                                var EyA = cE.x[j] * EigVecs[q].x[1][j];
                                var ExB = cE.y[j] * EigVecs[q].y[0][j];
                                var EyB = cE.y[j] * EigVecs[q].y[1][j];
                                ExR[j] = Math.sqrt(Math.pow(ExA, 2) + Math.pow(ExB, 2));
                                EyR[j] = Math.sqrt(Math.pow(EyA, 2) + Math.pow(EyB, 2));
                                ExTheta[j] = Math.atan2(ExB, ExA);
                                EyTheta[j] = Math.atan2(EyB, EyA);
                                //Magnetic field
                                // var HxA = cH.x[j]*EigVecs[q].x[2][j];
                                // var HyA = cH.x[j]*EigVecs[q].x[3][j];
                                // var HxB = cH.y[j]*EigVecs[q].y[2][j];
                                // var HyB = cH.y[j]*EigVecs[q].y[3][j];
                                // HxR[j] = Math.sqrt(Math.pow(HxA,2)+Math.pow(HxB,2));
                                // HyR[j] = Math.sqrt(Math.pow(HyA,2)+Math.pow(HyB,2));
                                // HxTheta[j] = Math.atan2(HxB,HxA);
                                // HyTheta[j] = Math.atan2(HyB,HyA);
                            }
                            //electric field
                            ExrArray[q] = ExR;
                            EyrArray[q] = EyR;
                            ExthetaArray[q] = ExTheta;
                            EythetaArray[q] = EyTheta;
                            //magnetic field
                            // HxrArray[q] = HxR;
                            // HyrArray[q] = HyR;
                            // HxthetaArray[q] = HxTheta;
                            // HythetaArray[q] = HyTheta;

                            if (q + 1 < epsilon.length) {

                        // console.log("here tooman22233124");
                            try {

   cE = $scope.crystal.crystal.transferMatrices[q].dot(cE); // generates an exception
}
catch (e) {
   // statements to handle any exceptions
   console.log("errored out");
   logMyErrors(e); // pass exception object to error handler
}
                                
                                // console.log("here tooman222332");
                                // cH = crystal1.crystal.transferMatrices[q].dot(cH);
                                // console.log("c: "+c.x);
                            }

                        };
                    };
                    
                    // runsetup = false;
                    var layerNumber;
                    var lowerL = 0;
                    var upperL = $scope.length2D[0];
                    for (var ii = 0; ii < $scope.length2D.length; ii++) {
                        if (lowerL <= z && z <= upperL) {
                            layerNumber = ii;
                            break
                        } else {
                            lowerL = upperL;
                            upperL = upperL + $scope.length2D[ii + 1];
                        
                        }
                    }
                    
                    var Ex = ExrArray[layerNumber][0] * Math.cos(ExthetaArray[layerNumber][0] + EigVals[layerNumber][0].y * z - $scope.o * t) +
                        ExrArray[layerNumber][1] * Math.cos(ExthetaArray[layerNumber][1] + EigVals[layerNumber][1].y * z - $scope.o * t) +
                        ExrArray[layerNumber][2] * Math.cos(ExthetaArray[layerNumber][2] + EigVals[layerNumber][2].y * z - $scope.o * t) +
                        ExrArray[layerNumber][3] * Math.cos(ExthetaArray[layerNumber][3] + EigVals[layerNumber][3].y * z - $scope.o * t);

                   var  Ey = EyrArray[layerNumber][0] * Math.cos(EythetaArray[layerNumber][0] + EigVals[layerNumber][0].y * z - $scope.o * t) +
                        EyrArray[layerNumber][1] * Math.cos(EythetaArray[layerNumber][1] + EigVals[layerNumber][1].y * z - $scope.o * t) +
                        EyrArray[layerNumber][2] * Math.cos(EythetaArray[layerNumber][2] + EigVals[layerNumber][2].y * z - $scope.o * t) +
                        EyrArray[layerNumber][3] * Math.cos(EythetaArray[layerNumber][3] + EigVals[layerNumber][3].y * z - $scope.o * t);

                    // Hx = ExrArray[layerNumber][0]*Math.cos(HxthetaArray[layerNumber][0] + EigVals[layerNumber][0].y*z - o*t) +
                    //     ExrArray[layerNumber][1]*Math.cos(HxthetaArray[layerNumber][1] + EigVals[layerNumber][1].y*z - o*t) +
                    //     ExrArray[layerNumber][2]*Math.cos(HxthetaArray[layerNumber][2] + EigVals[layerNumber][2].y*z - o*t) +
                    //     ExrArray[layerNumber][3]*Math.cos(HxthetaArray[layerNumber][3] + EigVals[layerNumber][3].y*z - o*t);

                    // Hy = EyrArray[layerNumber][0]*Math.cos(HythetaArray[layerNumber][0] + EigVals[layerNumber][0].y*z - o*t) +
                    //     EyrArray[layerNumber][1]*Math.cos(HythetaArray[layerNumber][1] + EigVals[layerNumber][1].y*z - o*t) +
                    //     EyrArray[layerNumber][2]*Math.cos(HythetaArray[layerNumber][2] + EigVals[layerNumber][2].y*z - o*t) +
                    //     EyrArray[layerNumber][3]*Math.cos(HythetaArray[layerNumber][3] + EigVals[layerNumber][3].y*z - o*t);
                    // x = Math.cos(-5*z);
                    // y = Math.cos(2*x);

                    if (Ex > eXmax) {
                        // console.log("Ex" + Ex);
                        //eXmax++;
                       // addAnim("testcanvas", endRange);
                    }
                    emit(z, Ex, Ey);
                    emit(z, 0, 0);
                },
                items: 2,
                channels: 3,
                live: true,
            });

            // view.line({
            //   points: '#ElectricFieldPlot',
            //   color: 0x0074D9,
            //   width: 2,
            // });
            view.vector({
                points: '#ElectricFieldPlot',
                color: 0x0074D9,
                width: 1,
                start: true,
            });

            var HxrArray = new Array();
            var HxthetaArray = new Array();
            var HyrArray = new Array();
            var HythetaArray = new Array();

            view.interval({
                id: 'MagneticFieldPlot',
                width: endRange * 10, //fields.Ex.length,
                expr: function(emit, z, i, t) {
                    if (runsetup) {
                        var U = crystal1.scattering($scope.o, $scope.k1, $scope.k2, $scope.incoming);
                        //Magnetic field
                        var cxH = [$scope.incoming[0], $scope.incoming[1], U.x[2], U.x[3]];
                        var cyH = [0, 0, U.y[2], U.y[3]];
                        var cH = new numeric.T(cxH, cyH);

                        for (i = 0; i < epsilon.length; i++) {
                            EigVals[i] = emScattering.eigenvaluesIsotropic(epsilon[i], mu[i], $scope.k1, $scope.k2);
                            EigVecs[i] = emScattering.eigenvectorsIsotropic(epsilon[i], mu[i], $scope.k1, $scope.k2);
                            // console.log("EigVecs[i]: "+EigVecs[i].y[0][0]);//EigVecs[layernum].y[wavetype][vectornum]
                            // .x or .y for real and imaginary parts
                            // wavetype is 0 for ex, 1 for ey, 2 for hx, 3 for hy
                            var HxR = new Array();
                            var HxTheta = new Array();
                            var HyR = new Array();
                            var HyTheta = new Array();
                            for (var j = 0; j < 4; j++) {
                                var HxA = cH.x[j] * EigVecs[i].x[2][j];
                                var HyA = cH.x[j] * EigVecs[i].x[3][j];
                                var HxB = cH.y[j] * EigVecs[i].y[2][j];
                                var HyB = cH.y[j] * EigVecs[i].y[3][j];
                                HxR[j] = Math.sqrt(Math.pow(HxA, 2) + Math.pow(HxB, 2));
                                HyR[j] = Math.sqrt(Math.pow(HyA, 2) + Math.pow(HyB, 2));
                                HxTheta[j] = Math.atan2(HxB, HxA);
                                HyTheta[j] = Math.atan2(HyB, HyA);
                            }
                            HxrArray[i] = HxR;
                            HyrArray[i] = HyR;
                            HxthetaArray[i] = HxTheta;
                            HythetaArray[i] = HyTheta;

                            if (i + 1 < epsilon.length) {
                                cH = crystal1.crystal.transferMatrices[i].dot(cH);
                            }
                        };
                        runsetup = false;
                    };
                    var layerNumber;
                    var lowerL = 0;
                    var upperL = $scope.length2D[0];
                    for (var ii = 0; ii < $scope.length2D.length; ii++) {
                        if (lowerL <= z && z <= upperL) {
                            layerNumber = ii;
                            break
                        } else {
                            lowerL = upperL;
                            upperL = upperL + $scope.length2D[ii + 1];
                        }
                    }

                   var Hx = HxrArray[layerNumber][0] * Math.cos(HxthetaArray[layerNumber][0] + EigVals[layerNumber][0].y * z - $scope.o * t) +
                        HxrArray[layerNumber][1] * Math.cos(HxthetaArray[layerNumber][1] + EigVals[layerNumber][1].y * z - $scope.o * t) +
                        HxrArray[layerNumber][2] * Math.cos(HxthetaArray[layerNumber][2] + EigVals[layerNumber][2].y * z - $scope.o * t) +
                        HxrArray[layerNumber][3] * Math.cos(HxthetaArray[layerNumber][3] + EigVals[layerNumber][3].y * z - $scope.o * t);

                    var Hy = HyrArray[layerNumber][0] * Math.cos(HythetaArray[layerNumber][0] + EigVals[layerNumber][0].y * z - $scope.o * t) +
                        HyrArray[layerNumber][1] * Math.cos(HythetaArray[layerNumber][1] + EigVals[layerNumber][1].y * z - $scope.o * t) +
                        HyrArray[layerNumber][2] * Math.cos(HythetaArray[layerNumber][2] + EigVals[layerNumber][2].y * z - $scope.o * t) +
                        HyrArray[layerNumber][3] * Math.cos(HythetaArray[layerNumber][3] + EigVals[layerNumber][3].y * z - $scope.o * t);
                    // x = Math.cos(-5*z);
                    // y = Math.cos(2*x);
                    // if(Hy>hXmax){ console.log("Hx"+Hy);
                    // hXmax++;
                    // addAnim("testcanvas",endRange);}

                    emit(z, Hx, Hy);
                    emit(z, 0, 0);
                    // emit(z, Hy, Hx);
                },
                items: 2,
                channels: 3,
                live: true,
            });

            // view.line({
            //   points: '#MagneticFieldPlot',
            //   color: 0xFF4136,
            //   width: 2,
            // });

            view.vector({
                points: '#MagneticFieldPlot',
                color: 0xFF4136,
                width: 1,
                start: true,
            });
            var visible = false;
            var madeVisible = false;
            var frame = function() {
                var parentVisibility = jelem.parent().css("visibility");
                    //console.log("doings things: ");
                if(parentVisibility != 'hidden'){
                    requestAnimationFrame(frame);
                    visible = true;
                    
                }
                else if(parentVisibility == 'hidden'){
                    visible = false;

                    requestAnimationFrame(frame);
                    renderer.domElement.style.visibility = parentVisibility;
                    return;
                }
                
                if(!madeVisible) {
                    renderer.domElement.style.visibility = parentVisibility; //wheretohide
                    madeVisible = true;
                }
                

                if(!visible)
                    console.log("looping while visible is false");
                //WIDTH = elem.offsetWidth - 10;
                //HEIGHT = elem.offsetHeight - 5;
                renderer.setSize(WIDTH, HEIGHT);

                //$scope.context.resize({ viewWidth: WIDTH, viewHeight: HEIGHT });
                $scope.context.frame();
                renderer.render(scene, camera);
                // console.log("this is happening");
                rgbColor = jelem.parent().css("background-color"); //0xFF851B;
                renderer.setClearColor(new THREE.Color(rgbColor), 1.0);

                
            };
            requestAnimationFrame(frame);
            //var off = $(elem).offset();
            //off.left += 5;
            //$("canvas").offset(off);
            // $("canvas").offset()

        }

        function createDispersionChart() {
            var dispersion = $scope.dispersion;
            var divName = "dispView";
            var width = "100%";
            var height = "100%";
            var data = new google.visualization.DataTable();
    data.addColumn('number', 'kz');
    for (var i = 0; i < dispersion.layersDispersions.length; i++) {
        data.addColumn('number', 'Layer ' + i);
    }
    var dataArray = new Array(dispersion.kz.length);
    for (var i = 0; i < dataArray.length; i++) {
        dataArray[i] = new Array(dispersion.layersDispersions.length + 1);
    }

    for (var i = 0; i < dispersion.kz.length; i++) {
        dataArray[i][0] = dispersion.kz[i];
        for (var j = 1; j < dispersion.layersDispersions.length + 1; j++) {
            dataArray[i][j] = dispersion.layersDispersions[j - 1][i];
            //this is where it fails
            //j not including first dispersion
        }
    }
    for (var i = 0; i < dataArray.length; i++) {
        data.addRows([
            dataArray[i]
        ]);
    }
    var options = {
        chart: {
            title: 'dispersion relationship'
        },
        chartArea: {
            left: 40,
            top: 5
        },
        width: width,
        height: height,
        vAxis: {
            viewWindow: {
                // min: -50,
                // max: 50
            }
        }
    };

    var chart = new google.visualization.LineChart(document.getElementById(divName));

    chart.draw(data, options);
        }

        function _createFieldChart_DEPRECATED() {
            var fields = $scope.field;
            var interfaces = $scope.crystal.materialInterfaces();



            var data = new google.visualization.DataTable();
            data.addColumn('number', 'z');
            data.addColumn('number', document.getElementById("shownVal").value);
            //Iterate through fields values

            for (var i = 0, N = fields.z.length; i < N; i++) {
                if (document.getElementById("shownVal").value == 'Eₓ') {
                    data.addRows([
                        [fields.z[i], fields.Ex[i]]
                    ]);
                }
                if (document.getElementById("shownVal").value == 'Eᵧ') {
                    data.addRows([
                        [fields.z[i], fields.Ey[i]]
                    ]);
                }
                if (document.getElementById("shownVal").value == 'Hₓ') {
                    data.addRows([
                        [fields.z[i], fields.Hx[i]]
                    ]);
                }
                if (document.getElementById("shownVal").value == 'Hᵧ') {
                    data.addRows([
                        [fields.z[i], fields.Hy[i]]
                    ]);
                }
                // console.log(fields.z[i] + " " + fields.Ex[i] + " " + fields.Ey[i] + " " + fields.Hx[i] + " " + fields.Hy[i]);
            }

            var options = {
                chart: {
                    title: document.getElementById("shownVal").value + ' Values in Relation to Z'
                },
                width: "100%",
                height: "100%",
                chartArea: {
                    left: 40,
                    top: 40
                }

            };

            function printInterfaces(dataTable) {
                var cli = this.getChartLayoutInterface();
                var chartArea = cli.getChartAreaBoundingBox();
                var cols = ['red', 'orange', 'yellow', 'green', 'blue', 'purple'];
                var w = cli.getXLocation(interfaces[1]) - cli.getXLocation(interfaces[0]);
                var y = cli.getChartAreaBoundingBox().height;
                console.log(interfaces);
                console.log("w:" + w);
                console.log("y:" + y);
                console.log("gety:" + Math.floor(cli.getYLocation(1)));
                console.log("bounding:" + cli.getChartAreaBoundingBox().top);
                var yBound = cli.getChartAreaBoundingBox().top;
                //       Element.prototype.remove = function() {
                // this.parentElement.removeChild(this);
                // }
                // //allows removal of elements without parents
                // NodeList.prototype.remove = HTMLCollection.prototype.remove = function() {
                // for(var i = this.length - 1; i >= 0; i--) {
                //     if(this[i] && this[i].parentElement) {
                //         this[i].parentElement.removeChild(this[i]);
                //     }
                //  }
                //  }
                var htmlClass = "addHere";
                if (htmlClass == "addHere2")
                    $(".overlay2").remove();
                else if (htmlClass == "addHere")
                    $(".overlay").remove();
                else if (htmlClass == "addHere3")
                    $(".overlay3").remove();
                for (var i = 0; i < interfaces.length - 1; i++) {
                    var w = cli.getXLocation(interfaces[i + 1]) - cli.getXLocation(interfaces[i]);

                    // document.getElementsByClassName('overlay' + i).remove();
                    addStruct(htmlClass, i, cols[i % 5], w, y);

                    // document.querySelector('.overlay').style.position = 'absolute';
                    // document.querySelector('.overlay').style.opacity = '.5';
                    // document.querySelector('.overlay').style.top = Math.floor(cli.getChartAreaBoundingBox().top) + "px";
                    // document.querySelector('.overlay').style.left = Math.floor(cli.getXLocation(interfaces[i])) + 15 + "px";
                };

                if (htmlClass == "addHere") {
                    var overlays = document.querySelectorAll('.overlay');
                    for (var j = 0; j < overlays.length; j++) {
                        overlays[j].style.position = 'absolute';
                        overlays[j].style.opacity = '.5';
                        overlays[j].style.top = Math.floor(cli.getChartAreaBoundingBox().top) + 86 + "px";
                        overlays[j].style.left = Math.floor(cli.getXLocation(interfaces[j])) + 16 + "px";

                    }
                } else if (htmlClass == "addHere2") {
                    var overlays = document.querySelectorAll('.overlay2');
                    for (var j = 0; j < overlays.length; j++) {
                        overlays[j].style.position = 'absolute';
                        overlays[j].style.opacity = '.5';
                        overlays[j].style.top = Math.floor(cli.getChartAreaBoundingBox().top) + 15 + "px";
                        overlays[j].style.left = Math.floor(cli.getXLocation(interfaces[j])) + 30 + "px";
                    }
                }



            }

            var chart = new google.visualization.LineChart(document.getElementById('structView'));
            google.visualization.events.addListener(chart, 'ready', printInterfaces.bind(chart, data));
            //var chart = new google.charts.Line(document.getElementById('linechart_material'));
            chart.draw(data, options);

            var myElements = document.querySelectorAll(".hiddenChart");
            for (var i = 0; i < myElements.length; i++) {
                myElements[i].style.opacity = 1;
            }
        }

        function createStructureChart() {
            var interfaces = $scope.crystal.materialInterfaces();
            var interfaceLength = interfaces[interfaces.length - 1];

            var data = google.visualization.arrayToDataTable([
                [{
                    f: 'Date',
                    type: 'number' // wont work whithout this
                }, {
                    f: 'Line',
                    type: 'number' // wont work whithout this
                }],
            ]);
            var jelem = $("#structureView");
            console.log("canvas element jquer:" + jelem.parent().css("background-color"));
            var rgbColor = jelem.parent().css("background-color");
            var options = {

                chart: {
                    title: 'dispersion relationship'
                },
                chartArea: {
                    left: 40,
                    top: 40
                },
                width: '100%',
                height: '100%',
                hAxis: {
                    gridlines: { 
                        count: (interfaceLength / 2),
                        color: 'transparent' 
                    },
                    viewWindow: {
                        min: 0,
                        max: $scope.totalLength //modify max by adding layer lengths, then apply to buildstructure button, then set up value placement of layers, then custom overlays
                    }
                },
                vAxis: {
                    //title: 'z',
                    textPosition: 'none',
                    gridlines: {
                         count: 10,
                         color: 'transparent'  
                    },
                    viewWindow: {
                        min: -1,
                        max: 1
                    }
                }
            };

            if (data.getNumberOfRows() == 0) { // if you have no data, add a data point and make the series transparent
                data.addRow([0, 0])
                options.series = {
                    0: {
                        color: 'transparent'
                    }
                }
            }

            function printInterfaces(dataTable) { //prints the colored squares on top  of the charts
                var cli = this.getChartLayoutInterface();
                var chartArea = cli.getChartAreaBoundingBox();
                var cols = ['red', 'orange', 'yellow', 'green', 'blue', 'purple'];
                var w = cli.getXLocation(interfaces[1]) - cli.getXLocation(interfaces[0]);
                var y = cli.getChartAreaBoundingBox().height;
                // console.log(interfaces);
                // console.log("w:" + w);
                // console.log("y:" + y);
                // console.log("gety:" + Math.floor(cli.getYLocation(1)));
                // console.log("bounding:" + cli.getChartAreaBoundingBox().top);
                var yBound = cli.getChartAreaBoundingBox().top;
                var htmlClass = "addHere3";
                if (htmlClass == "addHere3")
                    $(".overlay3").remove();
                for (var i = 0; i < interfaces.length - 1; i++) {
                    var w = cli.getXLocation(interfaces[i + 1]) - cli.getXLocation(interfaces[i]);

                    addStruct(htmlClass, i, cols[i % 5], w, y);
                };
                if (htmlClass == "addHere3") {
                    var overlays = document.querySelectorAll('.overlay3');
                    for (var j = 0; j < overlays.length; j++) {
                        overlays[j].style.position = 'absolute';
                        overlays[j].style.opacity = '.5';
                        overlays[j].style.top = Math.floor(cli.getChartAreaBoundingBox().top) + 64 + "px";
                        overlays[j].style.left = Math.floor(cli.getXLocation(interfaces[j])) + 16 + "px";
                    }
                }
            }

            var chart = new google.visualization.LineChart(document.getElementById('structureView'));
            google.visualization.events.addListener(chart, 'ready', printInterfaces.bind(chart, data)); //all from Google's tutorial https://developers.google.com/chart/interactive/docs/overlays

            chart.draw(data, options);
        }


    
});
