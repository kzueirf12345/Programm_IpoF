import matplotlib.pyplot as plt

fcube = open('build/model.txt')
fpgu = open('build/pgu.txt')
xarr_cube, yarr_cube, zarr_cube, xarr_pgu, yarr_pgu, zarr_pgu = [], [], [], [], [], []


st = set()
cnt = 0
for string in fcube:
    x, y, z = map(float, string.split())
    xarr_cube.append(x)
    yarr_cube.append(y)
    zarr_cube.append(z)
    if (xarr_cube[-1], yarr_cube[-1], zarr_cube[-1]) in st:
        cnt += 1
    st.add((xarr_cube[-1], yarr_cube[-1], zarr_cube[-1]));


for string in fpgu:
    x, y, z = map(float, string.split())
    xarr_pgu.append(x)
    yarr_pgu.append(y)
    zarr_pgu.append(z)
    if (xarr_pgu[-1], yarr_pgu[-1], zarr_pgu[-1]) in st:
        cnt += 1
    st.add((xarr_pgu[-1], yarr_pgu[-1], zarr_pgu[-1]));

fig = plt.figure()
ax = plt.axes(projection='3d')
ax.scatter(xarr_cube, yarr_cube, zarr_cube, color="green")
ax.scatter(xarr_pgu, yarr_pgu, zarr_pgu, color="red")
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
plt.show()