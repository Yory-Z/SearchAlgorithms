# Searching Algorithms
<h1>The implementation, complexity analyses and performance test of Sequence Tree, Binary Searching Tree and
Red Black Tree</h1>

<h2>Building time cause analysis:</h2>
Binary Searching Tree build cause time: 0.743 S<br/>
Sequence Tree build cause time: 16.461 S<br/>
All words: 1534284, Binary tree's words(no duplicate): 1360
<br/>

<h2>Building Time and MidOrder  cause analysis:</h2>
<h3>The data set is almost ordered</h3>
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

<h3>The data set is unordered</h3>
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
