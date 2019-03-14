//Global Namespace
var EigenCalc = EigenCalc || {};

/**
 * GetEigenvaluesAndEigenvectors
 * ----------------------
 * Gets Eigenvalues and Eigenvectors of the block matrix
 * using a special algorithm.
 * 
 * @param Matrix a 
 */
EigenCalc.getEigenvaluesAndEigenvectors = function(a) {
    var eigenvalues = new Array();
    var eigenvectors = new Array();

    var aBlocks = doesMatrixHaveZeroBlocks(a);

    if(aBlocks.hasBlocks) {
        var A = aBlocks.A, B = aBlocks.B;

        //Eigenvalues and eigenvectors of AB
        var eigen = getEigValsAndVecsOf2x2(math.multiply(A, B));

        //For loop does 1-4
        for(let i = 1; i <= 4; i++) {
            var index = Math.floor((i-1)/2);                                            //Gets index 0 for i=1,2 and 1 for i=3,4

            var eigenvalue = eigen.eigenvalues[index];                                  //Gets eigenvalue of AB

            if(i % 2 == 0) eigenvalues.push(math.multiply(-1, math.sqrt(eigenvalue)));  //Sets negative eigenvalue when i % 2 is 0
            else eigenvalues.push(math.sqrt(eigenvalue));                               //Sets positive eigenvalue otherwise

            var eigenvector = math.zeros(a.size()[0], 1);                               //Creates eigenvector format

            var u = matrixMultiplication(B, eigen.eigenvectors[index]);                 //u = B * vi

            var lambdaV = math.multiply(eigenvalues[i-1], eigen.eigenvectors[index]);   //λi*vi

            //Sets λi*vi/u to vector
            eigenvector = math.subset(eigenvector, math.index(0, 0), math.subset(lambdaV, math.index(0,0)));
            eigenvector = math.subset(eigenvector, math.index(1, 0), math.subset(lambdaV, math.index(1,0)));
            eigenvector = math.subset(eigenvector, math.index(2, 0), math.subset(u, math.index(0,0)));
            eigenvector = math.subset(eigenvector, math.index(3, 0), math.subset(u, math.index(1,0)));

            eigenvector = math.divide(eigenvector, vectorNorm(eigenvector));            //Divides the norm out of the vector

            eigenvectors.push(math.transpose(eigenvector).toArray()[0]);                //Pushes eigenvector to array
        }

        eigenvectors = math.matrix(eigenvectors);                                       //Converts the eigenvectors to a dense matrix
    } else {
        //Will add something later if the issue arises.
    }

    return {eigenvalues: eigenvalues, eigenvectors: eigenvectors};
}

/**
 * Does Matrix Have Zero Blocks
 * -----------------------
 * Determines if the matrix is a 2x2 matrix of blocks
 * 
 * @param Matrix a 
 */
function doesMatrixHaveZeroBlocks(a) {
    var bool = false, m = a.size()[0], n = a.size()[1];

    if(m != n) return {hasBlocks: false};

    var blockSize = n / 2, blockArr = new Array(); 

    blockArr.push(math.subset(a, math.index(math.range(0, blockSize), math.range(0, blockSize))));
    blockArr.push(math.subset(a, math.index(math.range(0, blockSize), math.range(blockSize, n))));
    blockArr.push(math.subset(a, math.index(math.range(blockSize, n), math.range(0, blockSize))));
    blockArr.push(math.subset(a, math.index(math.range(blockSize, n), math.range(blockSize, n))));

    var A, B, zeroBlocks = 0;

    for(let i = 0; i < blockArr.length; i++) {
        if(isZeroBlock(blockArr[i])) zeroBlocks++;
        else {
            if(A == null) A = blockArr[i];
            else if(B == null) B = blockArr[i];
        }
    }

    return {hasBlocks: true, A: A, B: B};
}

/**
 * Is Zero Matrix
 * --------------
 * Determines if the matrix has only zeros.
 * 
 * @param Matrix matrix 
 */
function isZeroBlock(matrix) {
    var hasNumber = false, matArr = matrix.toArray(), n = matrix.size()[0];

    for(let i = 0; i < n; i++) {
        for(let j = 0; j < n; j++) {
            if(matArr[i][j] != 0) hasNumber = true;
        }
    }

    return !hasNumber;
}

/**
 * Gets Eigenvalues and Eigenvectors of 2x2 Matrix
 * -----------------------------------------------
 * Takes in a 2x2 matrix and returns the eigenvalues
 * and eigenvectors.
 * 
 * @param Matrix mat - 2x2 matrix
 */
function getEigValsAndVecsOf2x2(mat) {
    var eigvals = new Array(), eigvecs = new Array();

    var a = math.subset(mat, math.index(0, 0)),
        b = math.subset(mat, math.index(0, 1)),
        c = math.subset(mat, math.index(1, 0)),
        d = math.subset(mat, math.index(1, 1));

    var T = math.multiply(-1, math.add(a, d)), D = math.subtract(math.multiply(a, d), math.multiply(b, c));

    var discriminant = math.subtract(math.pow(T, 2), math.multiply(4, D));

    if(math.compare(discriminant.re, 0) > 0){
        var root1 = math.divide(math.add(math.multiply(-1, T), math.sqrt(discriminant)), 2);
        var root2 = math.divide(math.subtract(math.multiply(-1, T), math.sqrt(discriminant)), 2);

        eigvals.push(math.complex(root1));
        eigvals.push(math.complex(root2));
    } else if(math.compare(discriminant.re, 0) == 0){
        var root = math.divide(math.multiply(-1, T), 2);

        eigvals.push(math.complex(root));
        eigvals.push(math.complex(0));
    } else {
        var real = math.divide(math.multiply(-1, T), 2);
        var i = math.divide(math.sqrt(math.multiply(-1, discriminant)), 2);

        eigvals.push(math.complex({ re: real, im: i }));
        eigvals.push(math.complex({ re: real, im: -i }));
    }

    var lambda1 = eigvals[0], lambda2 = eigvals[1];

    eigvecs[0] = math.zeros(2, 1);
    eigvecs[1] = math.zeros(2, 1);

    eigvecs[0] = findEigenvector(eigvecs[0], lambda1, mat);
    eigvecs[1] = findEigenvector(eigvecs[1], lambda2, mat);

    return {eigenvalues: eigvals, eigenvectors: eigvecs};
}

/**
 * Find Eigenvector
 * ----------------
 * Finds the eigenvector of a 2x2 matrix using
 * lambda a, and b of the matrix.
 * 
 * http://croninprojects.org/Vince/Geodesy/FindingEigenvectors.pdf
 * 
 * @param Matrix vector 
 * @param ComplexNumber lambda 
 * @param ComplexNumber a 
 * @param ComplexNumber b 
 */
function findEigenvector(vector, lambda, mat) {
    var a = math.subset(mat, math.index(0, 0)),
        b = math.subset(mat, math.index(0, 1)),
        c = math.subset(mat, math.index(1, 0)),
        d = math.subset(mat, math.index(1, 1));

    var v1 = 1, v2 = math.divide(math.subtract(lambda, a), b);

    if(b == 0 && c == 0) {
        v2 = 0;

        if(lambda.re > 0 || lambda.im > 0) {
            vector = math.subset(vector, math.index(0,0), v1);
            vector = math.subset(vector, math.index(1,0), v2);
        } else if(lambda.re < 0 || lambda.im < 0) {
            vector = math.subset(vector, math.index(0,0), v2);
            vector = math.subset(vector, math.index(1,0), v1);
        }

        return vector;
    } else if(b == 0 && c != 0) {
        v1 = math.subtract(lambda, d);
        v2 = c;
    } else if(b != 0 && c == 0) {
        v1 = b;
        v2 = math.subtract(lambda, a);
    }

    var norm = math.sqrt(math.add(math.pow(v1, 2), math.pow(v2, 2)));

    v1 = math.divide(v1, norm);
    v2 = math.divide(v2, norm);

    vector = math.subset(vector, math.index(0,0), v1);
    vector = math.subset(vector, math.index(1,0), v2);

    return vector;
}

/**
 * Matrix Multiplication
 * ------------------------
 * Takes two matrices (nxm and mxp) and multiplies them
 * into an nxp matrix.
 * 
 * If nxp matrix is 1x1, it returns a scalar value instead of
 * a matrix.
 * 
 * @param Matrix A 
 * @param Matrix B 
 * 
 * @throws Incorrect matrix size if matrices don't follow nxm and mxp criteria.
 */
function matrixMultiplication(A, B) {
    var aSize1 = A.size()[0], aSize2 = A.size()[1], bSize1 = B.size()[0], bSize2 = B.size()[1];

    var n = aSize1, m = aSize2, p = bSize2, C = math.zeros(n, p);

    if(aSize2 != bSize1) throw "Matrix A dimension n and Matrix B dimension m do not equal! The multiplication cannot be done. A(" + aSize1 + "," + aSize2 + ") and B(" + bSize1 + "," + bSize2 + ")";

    var matA = A.toArray(), matB = B.toArray(), matC = C.toArray();

    for(var i = 0; i < n; i++) {
        for(var j = 0; j < p; j++){
            var sum = 0;

            for(var k = 0; k < m; k++) {
                sum = math.add(sum, math.multiply(matA[i][k], matB[k][j]));
            }

            matC[i][j] = sum;
        }
    }

    if(n == 1 && p == 1){
        return matC[0][0];
    }

    return math.matrix(matC);
}

/**
 * Calculate L1 Norm of A Vector
 * -----------------------------
 * Calculatest the L1 norm of a provided
 * vector.
 * 
 * @param Vector v 
 */
function vectorNorm(v) {
    var m = v.size()[0], n = v.size()[1], sum = 0;

    if(m == 1 && n >= 1) {
        for(var i = 0; i < n; i++) {
            sum = math.add(sum, math.pow(math.abs(math.subset(v, math.index(0, i))), 2));
        }
    } else if(n == 1 && m >= 1) {
        for(var i = 0; i < m; i++) {
            sum = math.add(sum, math.pow(math.abs(math.subset(v, math.index(i, 0))), 2));
        }
    } else { throw "The provided matrix is not a valid vector!" }

    var ret = math.sqrt(sum);

    return ret;
}