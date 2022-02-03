def translate_object(x=0,y=0,z=0, object):
    matrix = np.matrix([
                        [1,0,0,x],
                        [0,1,0,y]
                        [0,0,1,z]
                        [0,0,0,1]
                       ])