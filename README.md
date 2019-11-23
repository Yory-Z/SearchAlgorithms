# SearchAlgorithms
The implementation, complexity analyses and performance test of Sequence Searching Tree, Binary Searching Tree and RedBlackTree

<strong>Build time cause analysis:</strong><br/>
binary tree build cause time: 0.743 S<br/>
sequence build cause time: 16.461 S<br/>
all words: 1534284, binary tree's words(no duplicate): 1360
<br/>

<strong>Building Time and MidOrder  cause analysis:</strong><br/>
<p>The data set is almost ordered</p>
<table>
    <thead>
        <tr>
            <td>Data Size</td>
            <td>Binary Searching Tree</td>
            <td>Red Black Tree</td>
        </tr>
    </thead>
    <tbody>
            <tr>
                <td>10000</td>
                <td>0 S</td>
                <td>0 S</td>
            </tr>
            <tr>
                <td>20000</td>
                <td>0 S</td>
                <td>0.016 S</td>
            </tr>
            <tr>
                <td>30000</td>
                <td>0.016 S</td>
                <td>0 S</td>
            </tr>
            <tr>
                <td>40000</td>
                <td>0.14 S</td>
                <td>0.016 S</td>
            </tr>
            <tr>
                <td>50000</td>
                <td>0.672 S</td>
                <td>0.016 S</td>
            </tr>
            <tr>
                <td>60000</td>
                <td>1.656 S</td>
                <td>0.015 S</td>
            </tr>
            <tr>
                <td>70000</td>
                <td>3.112 S</td>
                <td>0.032 S</td>
            </tr>
            <tr>
                <td>80000</td>
                <td>4.968 S</td>
                <td>0.032 S</td>
            </tr>
            <tr>
                <td>90000</td>
                <td>7.686 S</td>
                <td>0.031 S</td>
            </tr>
    </tbody>
</table>
<br/>

<p>The data set is unordered</p>
<table>
    <thead>
        <tr>
            <td>Data Size</td>
            <td>Binary Searching Tree</td>
            <td>Red Black Tree</td>
        </tr>
    </thead>
    <tbody>
            <tr>
                <td>10000</td>
                <td>0 S</td>
                <td>0 S</td>
            </tr>
            <tr>
                <td>20000</td>
                <td>0 S</td>
                <td>0 S</td>
            </tr>
            <tr>
                <td>40000</td>
                <td>0.016 S</td>
                <td>0.031 S</td>
            </tr>
            <tr>
                <td>80000</td>
                <td>0.032 S</td>
                <td>0.046 S</td>
            </tr>
            <tr>
                <td>160000</td>
                <td>0.031 S</td>
                <td>0.109 S</td>
            </tr>
            <tr>
                <td>320000</td>
                <td>0.078 S</td>
                <td>0.281 S</td>
            </tr>
            <tr>
                <td>640000</td>
                <td>0.14 S</td>
                <td>0.672 S</td>
            </tr>
            <tr>
                <td>1280000</td>
                <td>0.265 S</td>
                <td>1.516 S</td>
            </tr>
            <tr>
                <td>2560000</td>
                <td>0.516 S</td>
                <td>3.594 S</td>
            </tr>
            <tr>
                <td>5120000</td>
                <td>1.003 S</td>
                <td>8.716 S</td>
            </tr>
    </tbody>
</table>

<br/>
